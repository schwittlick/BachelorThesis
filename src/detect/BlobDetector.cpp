#include "BlobDetector.h"


BlobDetector::BlobDetector(void)
{
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
	delete blob_detect;
}

std::vector< cv::KeyPoint > BlobDetector::detect( cv::Mat * image )
{
	std::vector< cv::KeyPoint > keypoints;
	//blob_detect->detect( *image, keypoints, cv::Mat() );
	std::cout << "THE DETECTOR IS DISABLED. -> BlobDetector::detect" << keypoints.size() << " points." << std::endl;
	return keypoints;
}
