#include "OpticalFlowBlockMatching.h"


OpticalFlowBlockMatching::OpticalFlowBlockMatching(void) :
	lastMat( 10, 10, CV_8UC1 )
{
	lastMat = cv::gpu::GpuMat( cv::Mat::zeros( 10, 10, CV_8UC1 ) );
	std::cout << "Created the lastMat X=" << lastMat.cols << " Y:" << lastMat.rows << std::endl;
}

OpticalFlowBlockMatching::~OpticalFlowBlockMatching(void)
{
}

void OpticalFlowBlockMatching::apply( cv::gpu::GpuMat * mat )
{
	cv::gpu::GpuMat currentMat;
	cv::gpu::cvtColor( *mat, currentMat, CV_BGRA2GRAY );
	if( lastMat.size() != currentMat.size() )
	{
		lastMat = cv::gpu::GpuMat( currentMat );
	}
	
	cv::gpu::GpuMat velX( mat->size(), mat->type() );
	cv::gpu::GpuMat velY( mat->size(), mat->type() );

	cv::gpu::GpuMat buf( mat->size(), mat->type() );
	cv::gpu::GpuMat paintedFlow( mat->size(), CV_8UC3 );

	cv::gpu::calcOpticalFlowBM( lastMat, currentMat, cv::Size( 5, 5 ), cv::Size( 20, 20 ), cv::Size( 30, 30 ), true, velX, velY, buf );
	
	//drawFlow( buf, paintedFlow );

	currentMat.copyTo( lastMat );
}

void OpticalFlowBlockMatching::drawFlow( cv::gpu::GpuMat & flow, cv::gpu::GpuMat & buffer )
{
	if ( flow.channels() == 2 && buffer.channels() == 3 )
	{
		std::cout << "Here." << std::endl;
		cv::Mat xy[2]; //X,Y
		cv::Mat outputImage;
		flow.download( outputImage );
		cv::split( outputImage, xy );

		//calculate angle and magnitude
		cv::Mat magnitude, angle;
		//cv::cartToPolar( xy[0], xy[1], magnitude, angle, true );

		//translate magnitude to range [0;1]
		double mag_max;
		double mag_min = 0.1;
		//cv::minMaxLoc()
		cv::minMaxLoc( magnitude, &mag_min, &mag_max );
		magnitude.convertTo( magnitude, -1, 1.0/mag_max );

		//build hsv image
		cv::Mat _hsv[3], hsv;
		_hsv[0] = angle;
		_hsv[1] = cv::Mat::ones( angle.size(), CV_32F );
		_hsv[2] = magnitude;
		cv::merge( _hsv, 3, hsv );

		//convert to BGR and show
		cv::Mat bgr;//CV_32FC3 matrix
		cv::cvtColor(hsv, bgr, cv::COLOR_HSV2BGR);
		buffer.upload( bgr );
	} 
	else {
		throw 0;
	}
}
