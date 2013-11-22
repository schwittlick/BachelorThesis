#include "StandardImageProcessor.h"


StandardImageProcessor::StandardImageProcessor(void)
{
}


StandardImageProcessor::~StandardImageProcessor(void)
{
}

void StandardImageProcessor::makeBinary( cv::gpu::GpuMat * gpuImage )
{
	cv::initModule_nonfree();
	cv::Mat im;
	gpuImage->download( im );
	cv::cvtColor( im, im, CV_BGRA2GRAY );
	cv::threshold( im, im, 100, 255, 0 );
	cv::erode( im, im, cv::Mat(), cv::Point( -1, -1 ), 1, 1, 1 );
	cv::threshold( im, im, 100, 255, 0 );
	std::cout << "finished eroding, setting up blober " << std::endl;

	
	det.detect( &im );
	//points = det.detect( &im );
	std::cout << "finished detection." << std::endl;
	gpuImage->upload( im );
	std::cout << "done drawing keypoints" << std::endl;
}
