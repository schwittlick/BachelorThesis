#pragma once

#include <iostream>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/gpu/gpu.hpp"
#include <opencv2/contrib/contrib.hpp>
#include <opencv2/core/opengl_interop.hpp>

class OpticalFlowBlockMatching
{
public:
	OpticalFlowBlockMatching(void);
	~OpticalFlowBlockMatching(void);

	void apply( cv::gpu::GpuMat * mat );

private:
	cv::gpu::GpuMat lastMat;
	void drawFlow( cv::gpu::GpuMat & flow, cv::gpu::GpuMat & buffer );
};

