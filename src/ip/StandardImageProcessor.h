#pragma once

#include < iostream >
#include < vector >

#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/gpu/gpu.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/objdetect/objdetect.hpp>

class StandardImageProcessor
{
public:
	StandardImageProcessor(void);
	~StandardImageProcessor(void);

	void binary( cv::gpu::GpuMat * image, int threshold );

	void open( cv::gpu::GpuMat * image );
	void open( cv::gpu::GpuMat * image, int iterations );
	void close( cv::gpu::GpuMat * image );
	void close( cv::gpu::GpuMat * image, int iterations );
	void dilate( cv::gpu::GpuMat * image );
	void dilate( cv::gpu::GpuMat * image, int iterations );
	void erode( cv::gpu::GpuMat * image );
	void erode( cv::gpu::GpuMat * image, int iterations );

	void gradient( cv::gpu::GpuMat * image );
	void gradient( cv::gpu::GpuMat * image, int iterations );
	void topHat( cv::gpu::GpuMat * image );
	void topHat( cv::gpu::GpuMat * image, int iterations );
	void blackHat( cv::gpu::GpuMat * image );
	void blackHat( cv::gpu::GpuMat * image, int iterations );	

	void setKernelSize( int _kernelSize );

private:
	int kernelSize;
	cv::Mat kernel;
};

