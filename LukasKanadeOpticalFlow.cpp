#include "LukasKanadeOpticalFlow.h"
#include "flow_functions.h"


LukasKanadeOpticalFlow::LukasKanadeOpticalFlow(void) :
	isInitialized( false ),
	winSize( 11 ),
	maxLevel( 4 ),
	iters( 3 ),
	resize_img( false ),
	rfactor( 2.0 )
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

cv::Mat * LukasKanadeOpticalFlow::apply( cv::Mat * _frame1_rgb_ )
{
	if( isInitialized == false )
	{
		frame1_rgb_ = *_frame1_rgb_;

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

		isInitialized = true;
	}


	if( nframes >= 1 )
	{
		//gettimeofday(&tod1,NULL);
		//t1 = tod1.tv_sec + tod1.tv_usec / 1000000.0;

		// Upload images to the GPU
		frame1GPU.upload(frame1);
		frame0GPU.upload(frame0);

		// Do the dense optical flow
		dflow.dense(frame0GPU,frame1GPU,uGPU,vGPU);

		uGPU.download(imgU);
		vGPU.download(imgV);

		//gettimeofday(&tod1,NULL);
		//t2 = tod1.tv_sec + tod1.tv_usec / 1000000.0;
		tdflow = 1000.0*(t2-t1);
	}

	if( nframes >= 1 )
	{
		//gettimeofday(&tod1,NULL);
		//t1 = tod1.tv_sec + tod1.tv_usec / 1000000.0;

		// Draw the optical flow results
		//drawColorField(imgU,imgV,flow_rgb);

		frame1_rgb.copyTo(motion_flow);
		drawMotionField(imgU,imgV,motion_flow,15,15,.0,1.0,CV_RGB(0,255,0));

		// Visualization
		//imshow("Dense Flow",motion_flow);
		//imshow("Motion Flow",flow_rgb);
		//motion_flow.copyTo( *_frame1_rgb_ );
		//_frame1_rgb_->setTo( motion_flow );

		//waitKey(3);

		//gettimeofday(&tod1,NULL);
		//t2 = tod1.tv_sec + tod1.tv_usec / 1000000.0;
		//tvis = 1000.0*(t2-t1);
	}

	// Set the information for the previous frame
	frame1_rgb.copyTo(frame0_rgb);
	cvtColor(frame0_rgb,frame0,CV_BGR2GRAY);

	// Read the next frame
	nframes++;

	//_frame1_rgb_.copyTo( frame1_rgb_ );

	frame1_rgb_ = *_frame1_rgb_;

	if( frame1_rgb_.empty() == false )
	{
		if( resize_img == true )
		{
			cv::resize(frame1_rgb_,frame1_rgb,cv::Size(width,height),0,0,cv::INTER_LINEAR);
		}
		else
		{
			frame1_rgb_.copyTo(frame1_rgb);
		}

		cvtColor(frame1_rgb,frame1,CV_BGR2GRAY);
	}

	std::cout << "Frame Number: " << nframes << std::endl;

	return &motion_flow;
}
