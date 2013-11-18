#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/photo/photo.hpp>

class Denoiser
{
public:
	Denoiser(void);
	~Denoiser(void);

	static void applyDenoise( cv::Mat * image, int amount );
};

