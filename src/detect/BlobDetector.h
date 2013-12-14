#pragma once

#include < vector >
#include < iostream >
#include < string >
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/gpu/gpu.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/legacy/blobtrack.hpp"

#include "BlobDetectorDialog.h"

#include "QWidget"
#include "QObject"

class BlobDetector
{
public:
	BlobDetector( void );
	~BlobDetector( void );

	std::vector< cv::KeyPoint > detect( cv::Mat * image );

	std::vector< cv::KeyPoint > keypoints;
	cv::SimpleBlobDetector::Params params;
	cv::FeatureDetector * blob_detect;

//public slots:
	
	void setMinDistBetweenBlobs( int _minDist );
	
	void setMinRepeatablity( int _minRepeatability );
	
	void toggleFilterByArea( void );
	void setMinAre( int _minArea );
	void setMaxArea( int _maxArea );

	void toggleFilterByColor( void );
	void setThresholdStep( int _thresholdStep );
	void setMinThreshold( int _minThreshold );
	void setMaxThreshold( int _maxThreshold );
	

	void toggleFilterByCircularity( void );
	void setMinCircularity( int _minCircularity );
	void setMaxCircularity( int _maxCircularity );

	void toggleFilterByInertia( void );
	void setMinIntertiaRatio( int _minInertiaRatio );
	void setMaxInertiaRatio( int _maxIntertiaRatio );

	void toggleFilterByConvexity( void );
	void setMinConvexity( int _minConvexity );
	void setMaxConvexity( int _maxConvexity );
	
private:
	//BlobDetectorDialog * config;
};

