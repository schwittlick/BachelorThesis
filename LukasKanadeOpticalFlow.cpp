#include "LukasKanadeOpticalFlow.h"
#include "flow_functions.h"


LukasKanadeOpticalFlow::LukasKanadeOpticalFlow(void) :
	isInitialized( false ),
	winSize( 11 ),
	maxLevel( 4 ),
	iters( 3 ),
	resize_img( true ),
	rfactor( 2.0 ),
	downloadUploadTimer(),
	drawFlowTimer()
{
	nframes = width = height = 0;
	t1 = t2 = tdflow = tvis = 0.0;

	dflow.maxLevel = maxLevel;
	dflow.winSize = cv::Size(winSize,winSize);
	dflow.iters = iters;

	cv::gpu::setDevice( 0 );

	std::cout << "LukasKanadeOpticalFlow instantiated. " << std::endl;
}


LukasKanadeOpticalFlow::~LukasKanadeOpticalFlow( void )
{
}

cv::Mat * LukasKanadeOpticalFlow::apply( cv::Mat * _frame1_rgb_, bool motionOrColorFieldIndicator )
{
	if( isInitialized == false )
	{
		resizeAndSetupRescources( _frame1_rgb_ );

		isInitialized = true;
	}

	downloadUploadTimer.start();

	// Upload images to the GPU
	frame1GPU.upload(frame1);
	frame0GPU.upload(frame0);

	// Do the dense optical flow
	dflow.dense(frame0GPU,frame1GPU,uGPU,vGPU);

	uGPU.download(imgU);
	vGPU.download(imgV);

	downloadUploadTimer.stop();
	downloadUploadTimer.store();

	drawFlowTimer.start();

	frame1_rgb.copyTo( motion_flow );
	drawFlow( motionOrColorFieldIndicator );

	drawFlowTimer.stop();
	drawFlowTimer.store();	

	// Set the information for the previous frame
	frame1_rgb.copyTo( frame0_rgb );
	cvtColor( frame0_rgb, frame0, CV_BGR2GRAY );

	// get the next frame
	frame1_rgb_ = *_frame1_rgb_;

	resizeNewImage();

	return returnDrawnMotionFlow( motionOrColorFieldIndicator );
}

void LukasKanadeOpticalFlow::setIters( int _iters )
{
	this->iters = _iters;
	this->dflow.iters = this->iters;
}

void LukasKanadeOpticalFlow::setWinSize( int _winSize )
{
	this->winSize = _winSize;
	this->dflow.winSize = cv::Size( this->winSize, this->winSize );
}

void LukasKanadeOpticalFlow::setMaxLevel( int _maxLevel )
{
	this->maxLevel = _maxLevel;
	this->dflow.maxLevel = this->maxLevel;
}

void LukasKanadeOpticalFlow::resizeAndSetupRescources( cv::Mat * mat )
{
	frame1_rgb_ = *mat;

	if( resize_img == true )
	{
		frame1_rgb = cv::Mat(cv::Size(cvRound(frame1_rgb_.cols/rfactor),cvRound(frame1_rgb_.rows/rfactor)),CV_8UC3);
		width = frame1_rgb.cols;
		height = frame1_rgb.rows;

		cv::resize(frame1_rgb_,frame1_rgb,cv::Size(width,height),0,0,cv::INTER_LINEAR);
	}
	else
	{
		frame1_rgb = cv::Mat(cv::Size(frame1_rgb_.cols,frame1_rgb_.rows),CV_8UC3);
		width = frame1_rgb.cols;
		height = frame1_rgb.rows;
		frame1_rgb_.copyTo(frame1_rgb);
	}

	// Allocate memory for the images
	frame0_rgb = cv::Mat(cv::Size(width,height),CV_8UC3);
	frame0 = cv::Mat(cv::Size(width,height),CV_8UC1);
	frame1 = cv::Mat(cv::Size(width,height),CV_8UC1);
	flow_rgb = cv::Mat(cv::Size(width,height),CV_8UC3);
	motion_flow = cv::Mat(cv::Size(width,height),CV_8UC3);

	// Convert the image to grey and float
	cvtColor(frame1_rgb,frame1,CV_BGR2GRAY);
}

void LukasKanadeOpticalFlow::drawFlow( bool motionOrColorField )
{
	// Draw the optical flow results
	if( motionOrColorField )
	{
		drawColorField(imgU,imgV,flow_rgb);
	}
	else
	{
		drawMotionField( imgU, imgV, motion_flow, 5, 5, 0.0, 40.0, 1.0, CV_RGB( 230, 230, 230 ) );
	}
}

cv::Mat * LukasKanadeOpticalFlow::returnDrawnMotionFlow( bool motionOrColorField )
{
	if( motionOrColorField )
	{
		return &flow_rgb;
	}
	else
	{
		return &motion_flow;
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

void LukasKanadeOpticalFlow::resizeNewImage( void )
{
	if( frame1_rgb_.empty() == false )
	{
		if( resize_img == true )
		{
			cv::resize( frame1_rgb_, frame1_rgb, cv::Size( width, height ), 0, 0, cv::INTER_LINEAR );
		}
		else
		{
			frame1_rgb_.copyTo( frame1_rgb );
		}

		cvtColor( frame1_rgb, frame1, CV_BGR2GRAY );
	}
}
