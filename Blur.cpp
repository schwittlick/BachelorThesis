#include "Blur.h"


Blur::Blur(void)
{
}


Blur::~Blur(void)
{
}

void Blur::applyBlur( enum Type type, cv::Mat * image, int amount )
{
	switch( type )
	{
	case Type::GAUSSIAN:
		applyGaussianBlur( image, amount );
		break;
	case Type::MEANS:
		applyMedianBlur( image, amount );
		break;
	case Type::NORMAL:
		applyNormalBlur( image, amount );
		 break;
	}
	
}

void Blur::applyGaussianBlur( cv::Mat * image, int amount )
{
	for( int i = 0; i < amount; i++ )
	{
		cv::GaussianBlur( *image, *image, cv::Size( 3, 3 ), 0.0, 0.0, 4 );
	}
}

void Blur::applyMedianBlur( cv::Mat * image, int amount )
{
	for( int i = 0; i < amount; i++ )
	{
		cv::medianBlur( *image, *image, 3 );
	}
}

void Blur::applyNormalBlur( cv::Mat * image, int amount )
{
	for( int i = 0; i < amount; i++ )
	{
		cv::blur( *image, *image, cv::Size( 3, 3), cv::Point( -1, -1 ), 4 );
	}
}
