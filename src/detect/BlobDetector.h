#pragma once

#include < vector >
#include < iostream >
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/gpu/gpu.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/objdetect/objdetect.hpp>



class BlobDetector
{
public:
	BlobDetector(void);
	~BlobDetector(void);

	std::vector< cv::KeyPoint > detect( cv::Mat * image );

	cv::SimpleBlobDetector::Params params;
	cv::FeatureDetector * blob_detect;
};

