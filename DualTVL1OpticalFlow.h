#pragma once

#include "opencv2/core/core.hpp"
#include "opencv2/gpu/gpu.hpp"
#include "opencv2/legacy/legacy.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/photo/photo.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/core/core_c.h"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/nonfree/ocl.hpp"

#include < string >

class DualTVL1OpticalFlow
{
public:
	DualTVL1OpticalFlow(void);
	~DualTVL1OpticalFlow(void);

	cv::gpu::GpuMat calcGPU( cv::gpu::GpuMat * _gpu_image );
	cv::Mat calc( cv::Mat * _image );

	double getTau( void );
	void setTau( double _tau );
	double getLambda( void );
	void setLambda( double _lambda );
	double getTheta( void );
	void setTheta( double _theta );
	int getNScales( void );
	void setNScales( int _nscales );
	int getWarps( void );
	void setWarps( int _warps );
	double getEpsilon( void );
	void setEpsilon( double _epsilon );
	int getIterations( void );
	void setIterations( int _iterations);

private:
	cv::Ptr< cv::DenseOpticalFlow > dualTvli1;
	cv::gpu::OpticalFlowDual_TVL1_GPU tvl1;
	cv::gpu::GpuMat previousImage;
	cv::Mat previousMat;
	bool firstTime;

	cv::gpu::GpuMat gpuFrame0, gpuFrame1, gpuFlowX, gpuFlowY, gpuFlow;
	cv::Mat cpuFrame0, cpuFrame1, cpuFlowX, cpuFlowY, cpuFlow;

	void drawOpticalFlow( const cv::Mat_<float>& flowx, const cv::Mat_<float>& flowy, cv::Mat& dst, float maxmotion = -1 );
	bool isFlowCorrect( cv::Point2f u );
	cv::Vec3b computeColor( float fx, float fy );

};

