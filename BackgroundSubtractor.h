#pragma once

#include <iostream>

#include "opencv2/core/core.hpp"
#include "opencv2/gpu/gpu.hpp"
#include "opencv2/highgui/highgui.hpp"

class BackgroundSubtractor
{
public:
	BackgroundSubtractor(void);
	~BackgroundSubtractor(void);

	static enum Type { FGD_STAT, MOG, MOG2, GMG };

	void applyBGS( cv::Mat & image, enum BackgroundSubtractor::Type method );

private:
	cv::Mat frame;

	cv::gpu::GpuMat d_frame;

	//cv::gpu::FGDStatModel fgd_stat;
	cv::gpu::MOG_GPU mog;
	cv::gpu::MOG2_GPU mog2;
	cv::gpu::GMG_GPU gmg;


	cv::gpu::GpuMat d_fgmask;
	cv::gpu::GpuMat d_fgimg;
	cv::gpu::GpuMat d_bgimg;

	cv::Mat fgmask;
	cv::Mat fgimg;
	cv::Mat bgimg;

};

