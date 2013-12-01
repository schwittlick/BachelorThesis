#include "LukasKanadeOpticalFlow.h"
#include "flow_functions.h"


LukasKanadeOpticalFlow::LukasKanadeOpticalFlow( QWidget *parent ) :
	QWidget( parent ),
	isInitialized( false ),
	winSize( 11 ),
	maxLevel( 4 ),
	iters( 3 ),
	resize_img( true ),
	rfactor( 2.0 ),
	isShowView( false )
	//downloadUploadTimer(),
	//drawFlowTimer()
{
	nframes = width = height = 0;
	t1 = t2 = tdflow = tvis = 0.0;

	dflow_lukaskanade.maxLevel = maxLevel;
	dflow_lukaskanade.winSize = cv::Size(winSize,winSize);
	dflow_lukaskanade.iters = iters;

	lukasKanadeOpticalFlowDialog = new LukasKanadeOpticalFLowDialog( ( QWidget * ) this );
	//lukasKanadeOpticalFlowDialog->show();

	connect( lukasKanadeOpticalFlowDialog, SIGNAL( maxLevelValueChanged( int ) ), this, SLOT( maxLevelChanged( int ) ) );
	connect( lukasKanadeOpticalFlowDialog, SIGNAL( itersValueChanged( int ) ), this, SLOT( itersChanged( int ) ) );

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
	// create new local copy
	cv::gpu::GpuMat newMat;
	// convert to 8bit greyscale
	cv::gpu::cvtColor( *_gpu_frame, newMat, CV_BGRA2GRAY );

	if( newMat.size() != last_gpu_frame.size() )
	{
		// if the roi was resized, resie the last_gpu_frame, too
		last_gpu_frame = cv::gpu::GpuMat( newMat.rows, newMat.cols, CV_8UC1 );
	}
	
	if( last_gpu_frame.type() == newMat.type() ) 
	{
		// do the flow calculation
		dflow_lukaskanade.dense( last_gpu_frame, newMat, uGPU, vGPU );
	}
	// copy the current frame to the last frame, necessary for computing the next flow
	newMat.copyTo( last_gpu_frame );

	cv::Mat uMat( uGPU );
	cv::Mat vMat( vGPU ); 
	std::cout << "neMat type:" << newMat.type() << std::endl;
	cv::gpu::cvtColor( newMat, newMat, CV_GRAY2BGR );

	cv::Mat drawMat( newMat.rows, newMat.cols, newMat.type() );

	
	//drawMotionField_GPU( uGPU, vGPU, newMat, 10, 10, 0.0, 40.0, 1.0, CV_RGB( 230, 230, 230 ) );
	drawColorField( uMat, vMat, drawMat );
	//drawMotionField( uMat, vMat, drawMat, 10, 10, 20, 100, 1.0, cv::Scalar( 255, 0, 0 ) );

	cv::cvtColor( drawMat, drawMat, CV_BGR2RGBA );

	_gpu_frame->upload( drawMat );
	//newMat.copyTo( *_gpu_frame );
}

void LukasKanadeOpticalFlow::drawMotionField_GPU(cv::gpu::GpuMat &imgU, cv::gpu::GpuMat &imgV, cv::gpu::GpuMat &imgMotion,
					 int xSpace, int ySpace, float minCutoff, float maxCutoff, float multiplier, CvScalar color)
{
	cv::Mat uMat( imgU );
	cv::Mat vMat( imgV );
	cv::Mat drawMat(cv::Size( imgU.size().width, imgU.size().height), CV_8UC3 );
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

			ptri = uMat.ptr<float>(y);
			deltaX = ptri[x];

			ptri = vMat.ptr<float>(y);
			deltaY = ptri[x];

			angle = atan2(deltaY, deltaX);
			hyp = sqrt(deltaX*deltaX + deltaY*deltaY);

			if( hyp > minCutoff && hyp < maxCutoff )
			{
				p1.x = p0.x + cvRound(multiplier*hyp*cos(angle));
				p1.y = p0.y + cvRound(multiplier*hyp*sin(angle));

				cv::line(drawMat,p0,p1,color,1,CV_AA,0);

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

	imgMotion.upload( drawMat );
}


/*
/** This function draws a vector field based on horizontal and vertical flow fields   
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
				
			}
		}
	}
	imgMotion.upload( drawMat );
}
*/

void LukasKanadeOpticalFlow::setIters( int _iters )
{
	dflow_lukaskanade.releaseMemory();
	this->iters = _iters;
	this->dflow_lukaskanade.iters = this->iters;
	this->dflow_lukaskanade.maxLevel = this->maxLevel;
}

void LukasKanadeOpticalFlow::setMaxLevel( int _maxLevel )
{
	dflow_lukaskanade.releaseMemory();
	this->maxLevel = _maxLevel;
	this->dflow_lukaskanade.maxLevel = this->maxLevel;
	this->dflow_lukaskanade.iters = this->iters;
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

void LukasKanadeOpticalFlow::maxLevelChanged( int _newMaxLevel )
{
	std::cout << "LukasKanadeOpticalFlow::maxLevelChanged to :" << _newMaxLevel << std::endl;
	this->setMaxLevel( _newMaxLevel );
}

void LukasKanadeOpticalFlow::itersChanged( int _newIters )
{
	std::cout << "LukasKanadeOpticalFlow::itersChanged to:" << _newIters << std::endl;
	this->setIters( _newIters );
}

void LukasKanadeOpticalFlow::openConfig( void )
{
	this->lukasKanadeOpticalFlowDialog->show();
	this->lukasKanadeOpticalFlowDialog->setFocus();
}

void LukasKanadeOpticalFlow::closeConfig( void )
{
	this->lukasKanadeOpticalFlowDialog->close();
}

void LukasKanadeOpticalFlow::toggleViewDisplay()
{
	isShowView = !isShowView;
	if( isShowView )
	{
		lukasKanadeOpticalFlowDialog->show();
	}
	else
	{
		lukasKanadeOpticalFlowDialog->close();
	}
}
