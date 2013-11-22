#pragma once

#include "opencv2/core/core.hpp"
#include "opencv2/gpu/gpu.hpp"

class ProcessingPipeline
{
public:
	ProcessingPipeline(void);
	~ProcessingPipeline(void);

	void addImage( cv::gpu::GpuMat * imageToBeProcessed );
	void start( void );
	cv::gpu::GpuMat getFinishedImage( void );

private:
	cv::gpu::GpuMat currentImage;
};

