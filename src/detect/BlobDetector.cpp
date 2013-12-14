#include "BlobDetector.h"

BlobDetector::BlobDetector( void ) 
{
	params.minDistBetweenBlobs = 100.0f;
	params.filterByInertia = false;
	params.filterByConvexity = false;
	params.filterByColor = true;
	params.filterByCircularity = false;
	params.filterByArea = true;
	params.minArea = 50.0f;
	params.maxArea = 50000.0f;
	// ... any other params you don't want default value

	//config = new BlobDetectorDialog( parent );

	blob_detect = new cv::SimpleBlobDetector( params );
	blob_detect->create("SimpleBlob");

	std::vector< std::string > params;
	blob_detect->getParams( params );
	std::string blobColorParamHelp = blob_detect->paramHelp( "blobColor" );
	std::cout << "blobColorParamHelp: " << blobColorParamHelp << std::endl;
	double minDistBetweenBlobs = blob_detect->getDouble( "minDistBetweenBlobs" );
	std::cout << "minDistBetweenBlobs: " << minDistBetweenBlobs << std::endl;
	setMinDistBetweenBlobs( 5 );
	minDistBetweenBlobs = blob_detect->getDouble( "minDistBetweenBlobs" );
	std::cout << "minDistBetweenBlobs: " << minDistBetweenBlobs << std::endl;
	std::cout << params.size() << std::endl;
	for( auto it = params.begin(); it != params.end(); ++it )
	{
		std::cout << ( *it ) << std::endl;
	}
	char c;
	std::cin >> c;
}


BlobDetector::~BlobDetector(void)
{
	delete blob_detect;
}

std::vector< cv::KeyPoint > BlobDetector::detect( cv::Mat * image )
{
	blob_detect->set( "minDistBetweenBlobs", 100.0 );
	cv::Mat grayImage;
	cv::cvtColor( *image, grayImage, CV_BGRA2GRAY );
	blob_detect->detect( grayImage, keypoints );
	cv::cvtColor( grayImage, grayImage, CV_GRAY2BGR );
	cv::drawKeypoints( grayImage, keypoints, grayImage, cv::Scalar::all( -1 ), cv::DrawMatchesFlags::DEFAULT );
	cv::cvtColor( grayImage, *image, CV_BGR2BGRA );
	//cv::TermCriteria crit;
	//std::cout << keypoints.size() << std::endl;
	//cv::cornerSubPix( *image, keypoints, cv::Size( 5, 5 ), cv::Size( -1, -1 ), crit );
	//cv::cvtColor( *image, *image, CV_GRAY2RGB );
	for( auto it = keypoints.begin(); it != keypoints.end(); ++it )
	{
		//cv::rectangle( *image, cv::Rect( it->pt.x - it->size , it->pt.y - it->size , it->size*4, it->size*4 ), cv::Scalar( 0, 255, 0 ), 3, 8, 0 );
	}
	//keypoints.at( 0 ).size

	return keypoints;
}

void BlobDetector::setMinDistBetweenBlobs( int _minDist )
{
	blob_detect->set( "minDistBetweenBlobs", static_cast< float > ( _minDist ) );
}

void BlobDetector::setMinRepeatablity( int _minRepeatability )
{
	blob_detect->set( "minRepeatablity", static_cast< float > ( _minRepeatability ) );
}

void BlobDetector::toggleFilterByArea( void )
{
	blob_detect->set( "filterByArea", !blob_detect->getBool( "filterByArea" ) );
}

void BlobDetector::setMinAre( int _minArea )
{
	blob_detect->set( "minArea", static_cast< float > ( _minArea ) );
}

void BlobDetector::setMaxArea( int _maxArea )
{
	blob_detect->set( "maxArea", static_cast< float > ( _maxArea ) );
}

void BlobDetector::toggleFilterByColor( void )
{
	blob_detect->set( "filterByColor", !blob_detect->getBool( "filterByColor" ) );
}

void BlobDetector::setThresholdStep( int _thresholdStep )
{
	blob_detect->set( "thresholdStep", static_cast< float > ( _thresholdStep ) );
}

void BlobDetector::setMinThreshold( int _minThreshold )
{
	blob_detect->set( "minThreshold", static_cast< float > ( _minThreshold ) );
}

void BlobDetector::setMaxThreshold( int _maxThreshold )
{
	blob_detect->set( "maxThreshold", static_cast< float > ( _maxThreshold ) );
}

void BlobDetector::toggleFilterByCircularity( void )
{
	blob_detect->set( "filterByCircularity", !blob_detect->getBool( "filterByCircularity" ) );
}

void BlobDetector::setMinCircularity( int _minCircularity )
{
	blob_detect->set( "minCircularity", static_cast< float > ( _minCircularity ) );
}

void BlobDetector::setMaxCircularity( int _maxCircularity )
{
	blob_detect->set( "maxCircularity", static_cast< float > ( _maxCircularity) );
}

void BlobDetector::toggleFilterByInertia( void )
{
	blob_detect->set( "filterByInertia", !blob_detect->getBool( "filterByInertia" ) );
}

void BlobDetector::setMinIntertiaRatio( int _minInertiaRatio )
{
	blob_detect->set( "minInertiaRatio", static_cast< float > ( _minInertiaRatio) );
}

void BlobDetector::setMaxInertiaRatio( int _maxIntertiaRatio )
{
	blob_detect->set( "maxIntertiaRatio", static_cast< float > ( _maxIntertiaRatio) );
}

void BlobDetector::toggleFilterByConvexity( void )
{
	blob_detect->set( "filterByConvexity", !blob_detect->getBool( "filterByConvexity" ) );
}

void BlobDetector::setMinConvexity( int _minConvexity )
{
	blob_detect->set( "minConvexity", static_cast< float > ( _minConvexity) );
}

void BlobDetector::setMaxConvexity( int _maxConvexity )
{
	blob_detect->set( "maxConvexity", static_cast< float > ( _maxConvexity) );
}