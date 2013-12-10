#pragma once

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

#include < vector >

#include "src/detect/FeatureDetector.h"

class OpticalFlowLukaskanade
{
public:
	OpticalFlowLukaskanade(void);
	~OpticalFlowLukaskanade(void);

	void calc( cv::Mat * image );

private:
	void computeGoodFeaturesToTrack( cv::Mat * image );
	void drawFlow( cv::Mat * image );

	cv::Mat previousImage;
	std::vector< cv::Point2f > previousPoints, currentPoints;

	cv::TermCriteria crit;
	cv::Size window_size;
	std::vector<uchar> status;
	std::vector<float> err;

	FeatureDetector featureDetector;

	bool firstTime;
	int counter;
	std::vector< cv::Point2f > boatPointsLeftToRight, boatPointsRightToLeft;
	cv::Rect r;
};

