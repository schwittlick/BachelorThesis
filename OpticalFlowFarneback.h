#pragma once

#include < vector >

#include "opencv2/core/core.hpp"
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

class OpticalFlowFarneback
{
public:
	// parameters and opticallfowdraw from here https://code.ros.org/trac/opencv/browser/trunk/opencv/samples/c/fback.cpp?rev=2271
	OpticalFlowFarneback(void);
	~OpticalFlowFarneback(void);

	std::vector< cv::Point > calc( cv::Mat * image );
	void drawOptFlowMap(const cv::Mat& flow, cv::Mat& cflowmap, int step, double scale, const cv::Scalar& color);

private:
	cv::Mat previousImage;
};

