#include "OpticalFlowFarneback.h"


OpticalFlowFarneback::OpticalFlowFarneback(void) :
	pyr_scale( 0.5 ),
	winSize( 15 ),
	levels( 3 ),
	iterations( 3 ),
	poly_n( 5 ),
	poly_sigma( 1.2 ),
	stepSize( 8 ),
	scale( 30.0 )

{
	gui = new OpticalFlowFarnebackConfigDialog( (QWidget * ) ( this ) );
	gui->show();
	previousImage = cv::Mat::zeros( 576, 720, CV_8UC1 );
}


OpticalFlowFarneback::~OpticalFlowFarneback(void)
{
	delete gui;
}

void OpticalFlowFarneback::calc( cv::Mat * image )
{
	if( image->size() != previousImage.size() )
	{
		previousImage = cv::Mat::zeros( image->rows, image->cols, CV_8UC1 );
	}

	cv::cvtColor( *image, *image, CV_BGRA2GRAY);

	cv::Mat outputImage;
	cv::calcOpticalFlowFarneback(previousImage, *image, outputImage, pyr_scale, levels, winSize, iterations, poly_n, poly_sigma, 0 );
	image->copyTo( previousImage );

	cv::Mat xy[2]; //X,Y
	cv::split(outputImage, xy);

	//calculate angle and magnitude
	cv::Mat magnitude, angle;
	cv::cartToPolar(xy[0], xy[1], magnitude, angle, true);

	//translate magnitude to range [0;1]
	double mag_max;
	double scond = 0.0;
	cv::minMaxLoc(magnitude, &scond, &mag_max);
	//cv::minMaxLoc()
	magnitude.convertTo(magnitude, -1, 1.0/mag_max);

	//build hsv image
	cv::Mat _hsv[3], hsv;
	_hsv[0] = angle;
	_hsv[1] = cv::Mat::ones(angle.size(), CV_32F);
	_hsv[2] = magnitude;
	cv::merge(_hsv, 3, hsv);

	//convert to BGR and show
	cv::Mat bgr;//CV_32FC3 matrix
	cv::cvtColor(hsv, bgr, cv::COLOR_HSV2BGR);

	drawOptFlowMap( outputImage, bgr, stepSize, scale, cv::Scalar( 255, 0, 0 ) );

	cv::cvtColor( *image, *image, CV_GRAY2BGR );
	//cv::imwrite( "image_farnflow.jpg", bgr );
	bgr.copyTo( *image );
	image->convertTo( *image, CV_8UC3 );
	cv::cvtColor( *image, *image, CV_BGR2BGRA );
}

void OpticalFlowFarneback::drawOptFlowMap( const cv::Mat& flow, cv::Mat& cflowmap, int step, double scale, const cv::Scalar& color )
{
	for(int y = 0; y < cflowmap.rows; y += step)
		for(int x = 0; x < cflowmap.cols; x += step)
		{
			const cv::Point2f& fxy = flow.at<cv::Point2f>(y, x);
			line(cflowmap, cv::Point(x,y), cv::Point(cvRound(x+fxy.x), cvRound(y+fxy.y)),
				color);
			//cv::circle(cflowmap, cv::Point(x,y), 1, color, -1);
		}
}

void OpticalFlowFarneback::setPyrScale( double _pyr_scale )
{
	this->pyr_scale = _pyr_scale;
}

void OpticalFlowFarneback::setPolySigma( double _poly_sigma )
{
	this->poly_sigma = _poly_sigma;
}

void OpticalFlowFarneback::setLevels( int _levels )
{
	this->levels = _levels;
}

void OpticalFlowFarneback::setWinSize( int _winSize )
{
	this->winSize = _winSize;
}

void OpticalFlowFarneback::setIterations( int _iterations )
{
	this->iterations = _iterations;
}

void OpticalFlowFarneback::setPolyN( int poly_n )
{
	this->poly_n = poly_n;
}

void OpticalFlowFarneback::changedWinSize( int _winSize )
{
	std::cout << "Changed WinSize: " << _winSize << std::endl;
	this->setWinSize( _winSize );
}

void OpticalFlowFarneback::changedPyrScale( int _pyr_scale )
{
	double pyrScale = _pyr_scale / 100.0;
	std::cout << "pyrscale: " << pyrScale << std::endl;
	this->setPyrScale( pyrScale );
}

void OpticalFlowFarneback::changedPolySigma( int _polySigma )
{

	double polySigma = _polySigma / 200.0;
	std::cout << "changed polysigma: " << polySigma << std::endl;
	this->setPolySigma( polySigma );
}

void OpticalFlowFarneback::changedLevels( int _levels )
{
	std::cout << "changed levels:" << _levels << std::endl;
	this->setLevels( _levels );
}

void OpticalFlowFarneback::changedIterations( int _iterations )
{
	std::cout << "changed iterations:" << _iterations << std::endl;
	this->setIterations( _iterations );
}

void OpticalFlowFarneback::changedPolyN( int _poly_n )
{
	std::cout << "changed polyn: " << _poly_n << std::endl;
	this->setPolyN( _poly_n );
}

void OpticalFlowFarneback::setStepSize( int _stepSize )
{
	this->stepSize = _stepSize;
}

void OpticalFlowFarneback::setScale( double _scale )
{
	this->scale = _scale;
}

void OpticalFlowFarneback::changedStepSize( int _stepsize )
{
	std::cout << "changed stepsize : " << _stepsize << std::endl;
	this->setStepSize( _stepsize );
}

void OpticalFlowFarneback::changedScale( int _scale )
{
	double scaleDraw = _scale / 20.0;
	std::cout << "changed scale: " << scaleDraw << std::endl;
	this->setScale( scaleDraw );
}
