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

#define NMAX_CHARACTERS 500
#define SAVE_RESULTS 0

class LukasKanadeOpticalFlow
{
public:
	LukasKanadeOpticalFlow(void);
	~LukasKanadeOpticalFlow(void);

	cv::Mat * apply( cv::Mat * _frame1_rgb_);

private:
	// Some global variables for the optical flow
	const int winSize;// = 11;
	const int maxLevel;// = 4;
	const int iters;// = 3; // the lower this is the more it reacts to tiny movements
	const bool resize_img;// = true;
	const float rfactor;// = 2.0;

	cv::gpu::PyrLKOpticalFlow dflow;
	cv::gpu::GpuMat frame0GPU, frame1GPU, uGPU, vGPU;
	cv::Mat frame0_rgb_, frame1_rgb_, frame0_rgb, frame1_rgb, frame0, frame1;
	cv::Mat imgU, imgV;
	cv::Mat motion_flow, flow_rgb;
	int nframes, width, height;
	double t1, t2, tdflow, tvis;
	char cad[NMAX_CHARACTERS];

	bool isInitialized;

};

