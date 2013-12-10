#include "OpticalFlowSF.h"


OpticalFlowSF::OpticalFlowSF(void) :
	firstTime( true )
{
	previousImage = cv::Mat::zeros( 576, 720, CV_8UC3 );
}


OpticalFlowSF::~OpticalFlowSF(void)
{
}

void OpticalFlowSF::calc( cv::Mat * _image )
{
	cv::Mat flow;

	cv::cvtColor( *_image, *_image, CV_BGRA2RGB );

	std::cout << "Type previous: " << previousImage.type() << std::endl;
	std::cout << "Type currrent: " << _image->type() << std::endl;

	if( firstTime ) 
	{
		_image->copyTo( previousImage );
		firstTime = false;
	}

	

	cv::calcOpticalFlowSF( previousImage, *_image, flow, 3, 2, 4 );

	std::cout << "Finished." << std::endl;

	cv::Mat xy[2];
	split(flow, xy);

	//calculate angle and magnitude
	cv::Mat magnitude, angle;
	cartToPolar(xy[0], xy[1], magnitude, angle, true);

	//translate magnitude to range [0;1]
	double mag_max;
	minMaxLoc(magnitude, 0, &mag_max);
	magnitude.convertTo(magnitude, -1, 1.0/mag_max);

	//build hsv image
	cv::Mat _hsv[3], hsv;
	_hsv[0] = angle;
	_hsv[1] = cv::Mat::ones(angle.size(), CV_32F);
	_hsv[2] = magnitude;
	merge(_hsv, 3, hsv);

	//convert to BGR and show
	cv::Mat bgr;//CV_32FC3 matrix
	cvtColor(hsv, bgr, cv::COLOR_HSV2BGR);

	bgr.copyTo( *_image );

	_image->copyTo( previousImage );
}
