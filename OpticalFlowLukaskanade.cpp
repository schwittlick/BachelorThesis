#include "OpticalFlowLukaskanade.h"


OpticalFlowLukaskanade::OpticalFlowLukaskanade(void) :
	crit( CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03 ),
	firstTime( true ),
	window_size(31, 31),
	counter( 0 )
{
	previousImage = cv::Mat::zeros( 576, 720, CV_8UC4 );
}


OpticalFlowLukaskanade::~OpticalFlowLukaskanade(void)
{
}

void OpticalFlowLukaskanade::calc( cv::Mat * image )
{
	computeGoodFeaturesToTrack( image );
	

	std::cout << "Type of image: " << image->type() << " Type of previous: " << previousImage.type() << std::endl;
	std::cout << "Found points: " << currentPoints.size() << " old Points count: " << previousPoints.size() << std::endl;

	
	cv::calcOpticalFlowPyrLK( previousImage, *image, previousPoints, currentPoints, status, err, window_size, 3, crit, 0, 0.001 );

	/*
	// Remove all tracking points with a bad status from the list.
	size_t i = 0;
	size_t k = 0;
	for (; i < this->currentPoints.size(); i++)
	{
		if (status[i])
		{
			this->currentPoints[k] = this->currentPoints[i];
			k++;
		}
	}
	this->currentPoints.resize(k);
	this->previousImage.resize(k);
	*/
	

	//previousPoints = currentPoints;
	std::swap( previousPoints, currentPoints );
	image->copyTo( previousImage );

	drawFlow( image );
	std::cout << "Lukas Kanade Optical Flow CPU computed " << currentPoints.size() << "points with flow." << std::endl;
	counter++;
}

void OpticalFlowLukaskanade::computeGoodFeaturesToTrack( cv::Mat * image )
{
	//currentPoints.clear();
	currentPoints = featureDetector.processGoodFeaturesToTrack_CPU( image );
	if( counter % 5 == 0 ) 
	{
		previousPoints = currentPoints;
		//firstTime = false;
	}
}

void OpticalFlowLukaskanade::drawFlow( cv::Mat * image )
{
	//cv::cvtColor( *image, *image, CV_GRAY2RGB );
	boatPointsLeftToRight.clear();
	boatPointsRightToLeft.clear();
	for( auto it = currentPoints.begin(), it2 = previousPoints.begin(); it != currentPoints.end(); ++it, ++it2 )
	{
		cv::Point2f current = *it;
		cv::Point2f prev = *it2;
		float distancex = current.x - prev.x;
		if( (distancex > 4 && distancex < 500 )  ) 
		{
			//cv::line( *image, current, prev, cv::Scalar( 0, 0, 255 ), 4, 8, 0 );
			boatPointsLeftToRight.push_back( current );
			boatPointsLeftToRight.push_back( prev );
		} else if ( distancex < -4 && distancex > -500 )
		{
			//cv::line( *image, current, prev, cv::Scalar( 0, 255, 0 ), 4, 8, 0 );
			boatPointsRightToLeft.push_back( current );
			boatPointsRightToLeft.push_back( prev );
		}
		//cv::point( *image, current, prev, cv::Scalar( 0, 0, 255 ), 5, 8, 0 );
		//cv::circle( *image, *it, 5, cv::Scalar( 255, 0, 0 ), 1, 8, 0 );
		//cv::circle( *image, *it2, 3, cv::Scalar( 0, 255, 0 ), 1, 8, 0 );
		
	}
	std::cout << "Now Finding boudning box for " << boatPointsLeftToRight.size() << " ponts." << std::endl;
	if( boatPointsLeftToRight.size() > 4 ) 
	{
		r = cv::boundingRect( boatPointsLeftToRight );
		cv::rectangle( *image, r, cv::Scalar( 255, 255, 0 ), 2, 8, 0 );
	}

	if( boatPointsRightToLeft.size() > 4 ) 
	{
		r = cv::boundingRect( boatPointsRightToLeft );
		cv::rectangle( *image, r, cv::Scalar( 0, 255, 255 ), 2, 8, 0 );
	}
}
