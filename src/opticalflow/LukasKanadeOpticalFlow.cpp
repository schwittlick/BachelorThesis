#include "LukasKanadeOpticalFlow.h"
#include "flow_functions.h"


LukasKanadeOpticalFlow::LukasKanadeOpticalFlow(void) :
	isInitialized( false ),
	winSize( 11 ),
	maxLevel( 4 ),
	iters( 3 ),
	resize_img( true ),
	rfactor( 2.0 )
	//downloadUploadTimer(),
	//drawFlowTimer()
{
	nframes = width = height = 0;
	t1 = t2 = tdflow = tvis = 0.0;

	dflow_lukaskanade.maxLevel = maxLevel;
	dflow_lukaskanade.winSize = cv::Size(winSize,winSize);
	dflow_lukaskanade.iters = iters;

	cv::gpu::setDevice( 0 );

	std::cout << "LukasKanadeOpticalFlow instantiated. " << std::endl;
}


LukasKanadeOpticalFlow::~LukasKanadeOpticalFlow( void )
{
}

cv::Mat LukasKanadeOpticalFlow::apply( cv::Mat * _frame1_rgb_, bool motionOrColorFieldIndicator )
{
	if( isInitialized == false )
	{
		resizeAndSetupRescources( _frame1_rgb_ );

		isInitialized = true;
	}

	downloadUploadTimer.start();

	// Upload images to the GPU
	currentFrameGPU.upload(currentFrameCPU);
	previousFrameGPU.upload(previousFrameCPU);

	// Do the dense optical flow
	dflow_lukaskanade.dense(previousFrameGPU,currentFrameGPU,uGPU,vGPU);
	//dflow.sparse()

	uGPU.download( uCPU );
	vGPU.download(vCPU);

	downloadUploadTimer.stop();
	downloadUploadTimer.store();

	drawFlowTimer.start();

	//frameToCompute.copyTo( motion_flow );
	//_frame1_rgb_->copyTo( motion_flow );
	//motion_flow = frameToCompute.clone();
	motion_flow = cv::Mat::zeros( width, height, CV_8UC3 );
	drawFlow( motionOrColorFieldIndicator );

	drawFlowTimer.stop();
	drawFlowTimer.store();	

	// Set the information for the previous frame
	frameToCompute.copyTo( frame0_rgb );
	cvtColor( frame0_rgb, previousFrameCPU, CV_BGR2GRAY );

	// get the next frame
	newFrameCPU = *_frame1_rgb_;

	resizeAndConvertToGray();
	return returnDrawnMotionFlow( motionOrColorFieldIndicator );
}

void LukasKanadeOpticalFlow::apply( cv::gpu::GpuMat * _gpu_frame )
{
	if( isInitialized == false )
	{
		//last_gpu_frame = cv::gpu::GpuMat( cv::Size( 720, 576 ), CV_8UC4 );
		_gpu_frame->copyTo( last_gpu_frame );
		cv::gpu::cvtColor( last_gpu_frame, last_gpu_frame, CV_BGRA2GRAY );
		isInitialized = true;
	}
	cv::gpu::cvtColor( *_gpu_frame, *_gpu_frame, CV_BGRA2GRAY );
	dflow_lukaskanade.dense( last_gpu_frame, *_gpu_frame, uGPU, vGPU );
	_gpu_frame->copyTo( last_gpu_frame );
	std::cout << "color type of gpuimage: " << _gpu_frame->type() << std::endl;
	cv::gpu::cvtColor( *_gpu_frame, *_gpu_frame, CV_GRAY2BGR );
	std::cout << "color type of gpuimage: " << _gpu_frame->type() << std::endl;
	drawMotionField_GPU( uGPU, vGPU, *_gpu_frame, 10, 10, 0.0, 40.0, 1.0, CV_RGB( 230, 230, 230 ) );
}

/** This function draws a vector field based on horizontal and vertical flow fields   */
void LukasKanadeOpticalFlow::drawMotionField_GPU(cv::gpu::GpuMat &imgU, cv::gpu::GpuMat &imgV, cv::gpu::GpuMat &imgMotion,
					 int xSpace, int ySpace, float minCutoff, float maxCutoff, float multiplier, CvScalar color)
{
	cv::Mat uMat( cv::Size( imgU.size().width, imgU.size().height), CV_8UC3 );
	cv::Mat vMat( cv::Size( imgU.size().width, imgU.size().height), CV_8UC3 );
	imgU.download( uMat );
	imgV.download( vMat );
	//std::cout << "Im starting to draw that shit." << std::endl;
	cv::Mat drawMat(cv::Size( imgU.size().width, imgU.size().height), CV_8UC3 );
	//std::cout << "created a mat.§" << std::endl;
	int x = 0, y = 0;
	float *ptri;
	float deltaX = 0.0, deltaY = 0.0, angle = 0.0, hyp = 0.0;
	cv::Point p0, p1;

	for( y = ySpace; y < uMat.rows; y += ySpace )
	{
		for(x = xSpace; x < uMat.cols; x += xSpace )
		{
			p0.x = x;
			p0.y = y;
			//std::cout << "getting this ptr." << std::endl;
			ptri = uMat.ptr<float>(y);
			//std::cout << "donre getting the ptr." << std::endl;
			deltaX = ptri[x];
			//std::cout << "copying over" << std::endl;
			ptri = vMat.ptr<float>(y);
			deltaY = ptri[x];

			angle = atan2(deltaY, deltaX);
			hyp = sqrt(deltaX*deltaX + deltaY*deltaY);
			//std::cout << "this is where the if starts." << std::endl;
			if( hyp > minCutoff && hyp < maxCutoff )
			{
				//std::cout << "im in the if." << std::endl;
				p1.x = p0.x + cvRound(multiplier*hyp*cos(angle));
				p1.y = p0.y + cvRound(multiplier*hyp*sin(angle));

				//std::cout << "start drawing a line." << std::endl;
				cv::line(drawMat,p0,p1,color,1,CV_AA,0);
				//std::cout << "finished drawing a line." << std::endl;

				/*
				p0.x = p1.x + cvRound(2*cos(angle-M_PI + M_PI/4));
				p0.y = p1.y + cvRound(2*sin(angle-M_PI + M_PI/4));
				cv::line( imgMotion, p0, p1, color,1, CV_AA, 0);

				p0.x = p1.x + cvRound(2*cos(angle-M_PI - M_PI/4));
				p0.y = p1.y + cvRound(2*sin(angle-M_PI - M_PI/4));
				cv::line( imgMotion, p0, p1, color,1, CV_AA, 0);
				*/
			}
		}
	}
	std::cout << "Done iterating" << std::endl;
	std::cout << "drawmat type : " << drawMat.type() << std::endl;
	std::cout << "imgmotion type: " << imgMotion.type() << std::endl;
	imgMotion.upload( drawMat );
}

void LukasKanadeOpticalFlow::setIters( int _iters )
{
	this->iters = _iters;
	this->dflow_lukaskanade.iters = this->iters;
}

void LukasKanadeOpticalFlow::setWinSize( int _winSize )
{
	this->winSize = _winSize;
	this->dflow_lukaskanade.winSize = cv::Size( this->winSize, this->winSize );
}

void LukasKanadeOpticalFlow::setMaxLevel( int _maxLevel )
{
	this->maxLevel = _maxLevel;
	this->dflow_lukaskanade.maxLevel = this->maxLevel;
}

void LukasKanadeOpticalFlow::resizeAndSetupRescources( cv::Mat * mat )
{
	newFrameCPU = *mat;

	if( resize_img == true )
	{
		frameToCompute = cv::Mat(cv::Size(cvRound(newFrameCPU.cols/rfactor),cvRound(newFrameCPU.rows/rfactor)),CV_8UC3);
		width = frameToCompute.cols;
		height = frameToCompute.rows;

		cv::resize(newFrameCPU,frameToCompute,cv::Size(width,height),0,0,cv::INTER_LINEAR);
	}
	else
	{
		frameToCompute = cv::Mat(cv::Size(newFrameCPU.cols,newFrameCPU.rows),CV_8UC3);
		width = frameToCompute.cols;
		height = frameToCompute.rows;
		newFrameCPU.copyTo(frameToCompute);
	}

	// Allocate memory for the images
	frame0_rgb = cv::Mat(cv::Size(width,height),CV_8UC3);
	previousFrameCPU = cv::Mat(cv::Size(width,height),CV_8UC1);
	currentFrameCPU = cv::Mat(cv::Size(width,height),CV_8UC1);
	flow_rgb = cv::Mat(cv::Size(width,height),CV_8UC3);
	motion_flow = cv::Mat(cv::Size(width,height),CV_8UC3);

	// Convert the image to grey and float
	cvtColor( frameToCompute, currentFrameCPU, CV_BGR2GRAY );
}

void LukasKanadeOpticalFlow::drawFlow( bool motionOrColorField )
{
	// Draw the optical flow results
	if( motionOrColorField )
	{
		drawColorField( uCPU, vCPU, flow_rgb );
	}
	else
	{
		drawMotionField( uCPU, vCPU, motion_flow, 5, 5, 10.0, 30.0, 1.0, CV_RGB( 230, 230, 230 ) );
	}
}

cv::Mat LukasKanadeOpticalFlow::returnDrawnMotionFlow( bool motionOrColorField )
{
	if( motionOrColorField )
	{
		return flow_rgb;
	}
	else
	{
		return motion_flow;
	}

}

int LukasKanadeOpticalFlow::getAverageDownUploadTime( void )
{
	return downloadUploadTimer.getAverageTime();
}

int LukasKanadeOpticalFlow::getAverageDrawMotionFieldTime( void )
{
	return drawFlowTimer.getAverageTime();
}

void LukasKanadeOpticalFlow::resizeAndConvertToGray( void )
{
	if( newFrameCPU.empty() == false )
	{
		if( resize_img == true )
		{
			cv::resize( newFrameCPU, frameToCompute, cv::Size( width, height ), 0, 0, cv::INTER_LINEAR );
		}
		else
		{
			newFrameCPU.copyTo( frameToCompute );
		}

		cvtColor( frameToCompute, currentFrameCPU, CV_BGR2GRAY );
	}
}

void LukasKanadeOpticalFlow::resizeAndSetupRescources_GPU( cv::gpu::GpuMat * gpu_mat )
{
	//frame1_rgb_ = *mat;

	if( resize_img == true )
	{
		frameToCompute = cv::Mat(cv::Size(cvRound(newFrameCPU.cols/rfactor),cvRound(newFrameCPU.rows/rfactor)),CV_8UC3);
		width = frameToCompute.cols;
		height = frameToCompute.rows;

		cv::resize(newFrameCPU,frameToCompute,cv::Size(width,height),0,0,cv::INTER_LINEAR);
	}
	else
	{
		frameToCompute = cv::Mat(cv::Size(newFrameCPU.cols,newFrameCPU.rows),CV_8UC3);
		width = frameToCompute.cols;
		height = frameToCompute.rows;
		newFrameCPU.copyTo(frameToCompute);
	}

	// Allocate memory for the images
	frame0_rgb = cv::Mat(cv::Size(width,height),CV_8UC3);
	previousFrameCPU = cv::Mat(cv::Size(width,height),CV_8UC1);
	currentFrameCPU = cv::Mat(cv::Size(width,height),CV_8UC1);
	flow_rgb = cv::Mat(cv::Size(width,height),CV_8UC3);
	motion_flow = cv::Mat(cv::Size(width,height),CV_8UC3);

	// Convert the image to grey and float
	cvtColor(frameToCompute,currentFrameCPU,CV_BGR2GRAY);
}
