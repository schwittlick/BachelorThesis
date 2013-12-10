#pragma once

#include < vector >
#include <iostream>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/gpu/gpu.hpp"
#include "opencv2/nonfree/features2d.hpp"

#include "src/detect/BlobDetector.h"


class FeatureDetector
{
public:
	FeatureDetector(void);
	~FeatureDetector(void);

	std::vector< cv::Point2f > processGoodFeaturesToTrack_CPU( cv::Mat * _image );
	void processGoodFeaturesToTrack_GPU( cv::gpu::GpuMat * _gpu_image );
	void processFASTFeatureDetection_GPU( cv::Mat * _image );
	void processHarrisCornerDetection_CPU( cv::Mat * _image );
	void processCornerMinEigenVal_CPU( cv::Mat * _image );
	void processSurfFeatureDetection_CPU( cv::Mat * _image );
	void processSURFFeatureDetection_GPU( cv::gpu::GpuMat * _image );
	void processSurf_OCL_FeatureDetection_GPU( cv::Mat * _image );
	void processSIFTFeatureDetection_GPU( cv::Mat * _image );
	void processHOGDetection_GPU( cv::gpu::GpuMat * _image );
	void processHOGDetection_CPU( cv::Mat * _image );
	void processBlobDetection( cv::gpu::GpuMat * _image );

	void drawPoints( cv::Mat * imageToDrawOn );

private:
	std::vector< cv::Point2f > featurePoints;
	cv::Mat previousMat;
	cv::gpu::GpuMat previousGpuMat;

	BlobDetector det;
	std::vector< cv::KeyPoint > points;

	void processPreCornerDetect( cv::Mat * _image );
};

