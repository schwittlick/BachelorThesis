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

#include "src/misc/Timer.h"

#include "src/opticalflow/flow_functions.h"
#include "lukaskanadeopticalflowdialog.h"

#include "QObject"
#include "QWidget"

#define NMAX_CHARACTERS 500
#define SAVE_RESULTS 0

class LukasKanadeOpticalFlow : public QWidget
{
	Q_OBJECT
public:
	LukasKanadeOpticalFlow( QWidget *parent = 0 );
	~LukasKanadeOpticalFlow(void);

	cv::Mat apply( cv::Mat * _frame1_rgb_, bool motionOrColorFieldIndicator );
	void apply( cv::gpu::GpuMat *_gpu_frame );

	void setMaxLevel( int _maxLevel );
	void setIters( int _iters );

	int getAverageDownUploadTime( void );
	int getAverageDrawMotionFieldTime( void );

	void toggleViewDisplay();
	

public slots:
	void maxLevelChanged( int _newMaxLevel );
	void itersChanged( int _newIters );
	void openConfig( void );
	void closeConfig( void );

private:
	bool isShowView;
	// Some global variables for the optical flow
	int winSize;// = 11;
	int maxLevel;// = 4;
	int iters;// = 3; // the lower this is the more it reacts to tiny movements
	bool resize_img;// = true;
	float rfactor;// = 2.0;

	LukasKanadeOpticalFLowDialog * lukasKanadeOpticalFlowDialog;

	cv::gpu::GpuMat last_gpu_frame;

	cv::gpu::PyrLKOpticalFlow dflow_lukaskanade;
	//cv::gpu::BroxOpticalFlow dflow_brox;
	//cv::gpu::FarnebackOpticalFlow dflow_farneback;
	cv::gpu::GpuMat previousFrameGPU, currentFrameGPU, uGPU, vGPU;
	cv::Mat frame0_rgb_, newFrameCPU, frame0_rgb, frameToCompute, previousFrameCPU, currentFrameCPU;
	cv::Mat uCPU, vCPU;
	cv::Mat motion_flow, flow_rgb;
	int nframes, width, height;
	double t1, t2, tdflow, tvis;
	char cad[NMAX_CHARACTERS];

	bool isInitialized;
	Timer downloadUploadTimer;
	Timer drawFlowTimer;
	void resizeAndSetupRescources( cv::Mat * mat );
	void resizeAndSetupRescources_GPU( cv::gpu::GpuMat * gpu_mat );
	void drawFlow( bool motionOrColorField );
	cv::Mat returnDrawnMotionFlow( bool motionOrColorField );
	void resizeAndConvertToGray( void );
	void drawMotionField_GPU(cv::gpu::GpuMat &imgU, cv::gpu::GpuMat &imgV, cv::gpu::GpuMat &imgMotion,
		int xSpace, int ySpace, float minCutoff, float maxCutoff, float multiplier, CvScalar color);
	

};

