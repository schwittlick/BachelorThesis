#include "FeatureDetector.h"


FeatureDetector::FeatureDetector(void)
{
	previousMat = cv::Mat::zeros( 720, 576, CV_8UC4 );
}


FeatureDetector::~FeatureDetector(void)
{
}

std::vector< cv::Point2f > FeatureDetector::processGoodFeaturesToTrack_CPU( cv::Mat * _image )
{
	cv::Mat imageGrayScale;
	if( _image->channels() == 3 )
	{
		cv::cvtColor( *_image, imageGrayScale, CV_BGR2GRAY );
	}
	else if( _image->channels() == 4)
	{
		cv::cvtColor( *_image, imageGrayScale, CV_BGRA2GRAY );
	}

	int maxCorners = 300;
	double qualityLevel = 0.01;
	double minDistance = 5;
	int blockSize = 3;
	bool useHarrisDetector = false;
	double k = 0.04;
	// this uses Shi-Tomasi Corner detection Method: http://docs.opencv.org/doc/tutorials/features2d/trackingmotion/good_features_to_track/good_features_to_track.html
	cv::goodFeaturesToTrack( imageGrayScale, featurePoints, maxCorners, qualityLevel, minDistance, cv::Mat(), blockSize, useHarrisDetector, k );
	cv::TermCriteria termCriteria( CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03 );
	//cv::cornerSubPix( imageGrayScale, featurePoints, cv::Size( 10, 10 ), cv::Size( -1, -1 ), termCriteria );

	std::cout << "Size: " << featurePoints.size() << std::endl;

	//this->drawPoints( _image );

	return featurePoints;
}

void FeatureDetector::processGoodFeaturesToTrack_GPU( cv::gpu::GpuMat * _gpu_image )
{

}

void FeatureDetector::processFASTFeatureDetection_GPU( cv::Mat * _image )
{

}

void FeatureDetector::processHarrisCornerDetection_CPU( cv::Mat * _image )
{

}

void FeatureDetector::processSURFFeatureDetection_GPU( cv::gpu::GpuMat * _image )
{

}

void FeatureDetector::processSurf_OCL_FeatureDetection_GPU( cv::Mat * _image )
{

}

void FeatureDetector::processSIFTFeatureDetection_GPU( cv::Mat * _image )
{

}

void FeatureDetector::processPreCornerDetect( cv::Mat * _image )
{

}

void FeatureDetector::drawPoints( cv::Mat * imageToDrawOn )
{
	for( int i = 0; i < featurePoints.size(); i++ )
	{ 
		cv::circle( *imageToDrawOn, featurePoints[i], 4, cv::Scalar(255, 0, 0), -1, 8, 0 ); 
	}
}

void FeatureDetector::processHOGDetection_GPU( cv::gpu::GpuMat * _image )
{
	std::vector<float> descriptorsValues;
	std::vector< cv::Point > foundLocations;
	cv::gpu::HOGDescriptor hog;
	//hog.compute( _image, descriptorsValues, cv::Size(0,0), cv::Size(0,0), foundLocations );
	hog.detect( *_image, foundLocations );
	std::cout << "Finished. Found " << foundLocations.size() << " points." << std::endl;
}

void FeatureDetector::processHOGDetection_CPU( cv::Mat * _image )
{

}

void FeatureDetector::processSurfFeatureDetection_CPU( cv::Mat * _image )
{
	int minHessian = 400;
	std::cout << "Started." << std::endl;
	cv::SurfFeatureDetector detector( minHessian );

	std::vector< cv::KeyPoint > keypoints_1, keypoints_2;

	detector.detect( *_image, keypoints_1 );
	detector.detect( previousMat, keypoints_2 );

	//-- Step 2: Calculate descriptors (feature vectors)
	cv::SurfDescriptorExtractor extractor;
	std::cout << "2" << std::endl;
	cv::Mat descriptors_1, descriptors_2;

	extractor.compute( *_image, keypoints_1, descriptors_1 );
	extractor.compute( previousMat, keypoints_2, descriptors_2 );
	std::cout << "3" << std::endl;
	//-- Step 3: Matching descriptor vectors with a brute force matcher
	cv::BFMatcher matcher( cv::NORM_L2 );
	std::vector< cv::DMatch > matches;
	std::cout << "4" << std::endl;
	matcher.match( descriptors_1, descriptors_2, matches );
	std::cout << "5" << std::endl;
	//-- Draw matches
	cv::Mat img_matches;
	drawMatches( *_image, keypoints_1, previousMat, keypoints_2, matches, img_matches );
	_image->copyTo( previousMat );
	img_matches.copyTo( *_image );
	
}
