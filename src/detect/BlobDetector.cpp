#include "BlobDetector.h"


BlobDetector::BlobDetector(void)
{
	cv::SimpleBlobDetector::Params params;
	params.minDistBetweenBlobs = 50.0f;
	params.filterByInertia = false;
	params.filterByConvexity = false;
	params.filterByColor = false;
	params.filterByCircularity = false;
	params.filterByArea = true;
	params.minArea = 100.0f;
	params.maxArea = 500.0f;
	// ... any other params you don't want default value

	blob_detect = new cv::SimpleBlobDetector( params );
	blob_detect->create("SimpleBlob");
}


BlobDetector::~BlobDetector(void)
{
}

std::vector< cv::KeyPoint > BlobDetector::detect( cv::Mat * image )
{
	cv::SimpleBlobDetector::Params params;
	params.minDistBetweenBlobs = 50.0f;
	params.filterByInertia = false;
	params.filterByConvexity = false;
	params.filterByColor = false;
	params.filterByCircularity = false;
	params.filterByArea = true;
	params.minArea = 100.0f;
	params.maxArea = 500.0f;
	// ... any other params you don't want default value

	cv::SimpleBlobDetector blo( params );
	

	std::vector<cv::KeyPoint> keypoints;
	blo.detect( *image, keypoints );
	std::cout << "finished detecting. found " << keypoints.size() << " points." << std::endl;
	return keypoints;
}
