#pragma once

#include < vector >

#include "opencv2/core/core.hpp"

class FeatureDetector
{
public:
	FeatureDetector(void);
	~FeatureDetector(void);

	void processGoodFeaturesToTrack_CPU( cv::Mat * _image );
	void processGoodFeaturesToTrack_GPU( cv::gpu::GpuMat * _gpu_image );
	void processFASTFeatureDetection_GPU( cv::Mat * _image );
	void processHarrisCornerDetection_CPU( cv::Mat * _image );
	void processCornerMinEigenVal_CPU( cv::Mat * _image );
	void processSURFFeatureDetection_GPU( cv::Mat * _image );
	void processSurf_OCL_FeatureDetection_GPU( cv::Mat * _image );
	void processSIFTFeatureDetection_GPU( cv::Mat * _image );

private:
	std::vector< cv::Point2f > featurePoints;

	void processPreCornerDetect( cv::Mat * _image );
};

