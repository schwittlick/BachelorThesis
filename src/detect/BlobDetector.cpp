#include "BlobDetector.h"


BlobDetector::BlobDetector(void)
{
	params.minDistBetweenBlobs = 50.0f;
	params.filterByInertia = false;
	params.filterByConvexity = false;
	params.filterByColor = false;
	params.filterByCircularity = false;
	params.filterByArea = true;
	params.minArea = 500.0f;
	params.maxArea = 5000000.0f;
	// ... any other params you don't want default value

	blob_detect = new cv::SimpleBlobDetector( params );
	blob_detect->create("SimpleBlob");
}


BlobDetector::~BlobDetector(void)
{
	delete blob_detect;
}

std::vector< cv::KeyPoint > BlobDetector::detect( cv::Mat * image )
{
	blob_detect->detect( *image, keypoints );
	//cv::drawKeypoints( *image, keypoints, *image, cv::Scalar( 255, 0, 255 ), 0 );
	cv::cvtColor( *image, *image, CV_GRAY2RGB );
	for( auto it = keypoints.begin(); it != keypoints.end(); ++it )
	{
		cv::rectangle( *image, cv::Rect( it->pt.x - it->size , it->pt.y - it->size , it->size*4, it->size*4 ), cv::Scalar( 0, 255, 0 ), 3, 8, 0 );
	}
	//keypoints.at( 0 ).size

	return keypoints;
}
