#pragma once

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class Blur
{
public:
	Blur(void);
	~Blur(void);

	enum Type { GAUSSIAN, MEANS, NORMAL };

	static void applyBlur( enum Blur::Type type, cv::Mat * image, int amount );
	
private:
	static void applyGaussianBlur( cv::Mat * image, int amount );
	static void applyMedianBlur( cv::Mat * image, int amount );
	static void applyNormalBlur( cv::Mat * image, int amount );
};

