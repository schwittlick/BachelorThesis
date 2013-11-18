#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <math.h>
#include <iostream>
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/gpu/gpu.hpp>

#include "Timer.h"

#define NMAX_CHARACTERS 500
#define SAVE_RESULTS 0

class LukasKanadeOpticalFlow
{
public:
	LukasKanadeOpticalFlow(void);
	~LukasKanadeOpticalFlow(void);

	cv::Mat * apply( cv::Mat * _frame1_rgb_, bool motionOrColorFieldIndicator );

	void setMaxLevel( int _maxLevel );
	void setWinSize( int _winSize );
	void setIters( int _iters );

	int getAverageDownUploadTime( void );
	int getAverageDrawMotionFieldTime( void );

private:
	// Some global variables for the optical flow
	int winSize;// = 11;
	int maxLevel;// = 4;
	int iters;// = 3; // the lower this is the more it reacts to tiny movements
	bool resize_img;// = true;
	float rfactor;// = 2.0;

	cv::gpu::PyrLKOpticalFlow dflow;
	cv::gpu::GpuMat frame0GPU, frame1GPU, uGPU, vGPU;
	cv::Mat frame0_rgb_, frame1_rgb_, frame0_rgb, frame1_rgb, frame0, frame1;
	cv::Mat imgU, imgV;
	cv::Mat motion_flow, flow_rgb;
	int nframes, width, height;
	double t1, t2, tdflow, tvis;
	char cad[NMAX_CHARACTERS];

	bool isInitialized;
	Timer downloadUploadTimer;
	Timer drawFlowTimer;
	void resizeAndSetupRescources( cv::Mat * mat );
	void drawFlow( bool motionOrColorField );
	cv::Mat * returnDrawnMotionFlow( bool motionOrColorField );
	void resizeNewImage( void );


};

