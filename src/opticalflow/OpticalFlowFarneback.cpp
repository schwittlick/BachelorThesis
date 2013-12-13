#include "OpticalFlowFarneback.h"


OpticalFlowFarneback::OpticalFlowFarneback( QWidget *parent ) :
	OpticalFlowMethod( parent ),
	pyr_scale( 0.5 ),
	winSize( 15 ),
	levels( 3 ),
	iterations( 3 ),
	poly_n( 5 ),
	poly_sigma( 1.2 ),
	stepSize( 8 ),
	scale( 30.0 ),
	minLength( 0 ),
	maxLength( 100 ),
	activated( false ),
	previousGpuImage( 20, 20, CV_8UC1 )
{
	gui = new OpticalFlowFarnebackConfigDialog( this );

	connect( gui, SIGNAL( changedWinSize( int ) ), this, SLOT( changedWinSize( int ) ) );
	connect( gui, SIGNAL( changedPyrScale( int ) ), this, SLOT( changedPyrScale( int ) ) );
	connect( gui, SIGNAL( changedPolySigma( int ) ), this, SLOT( changedPolySigma( int ) ) );
	connect( gui, SIGNAL( changedLevels( int ) ), this, SLOT( changedLevels( int ) ) );
	connect( gui, SIGNAL( changedIterations( int ) ), this, SLOT( changedIterations( int ) ) );
	connect( gui, SIGNAL( changedPolyN( int ) ), this, SLOT( changedPolyN( int ) ) );
	connect( gui, SIGNAL( changedStepSize( int ) ), this, SLOT( changedStepSize( int ) ) );
	connect( gui, SIGNAL( changedScale( int ) ), this, SLOT( changedScale( int ) ) );
	connect( gui, SIGNAL( changedMinLength( int ) ), this, SLOT( changedMinLength( int ) ) );
	connect( gui, SIGNAL( changedMaxLength( int ) ), this, SLOT( changedMaxLength( int ) ) );

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
	timer.start();
	cv::calcOpticalFlowFarneback(previousImage, *image, outputImage, pyr_scale, levels, winSize, iterations, poly_n, poly_sigma, 0 );
	timer.stop();
	timer.store();

	std::cout << "last:" << timer.getLatestStdString() << std::endl;
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

	bool drawIt = true;
	if( drawIt )
	{
		drawOptFlowMap( outputImage, bgr, stepSize, scale, cv::Scalar( 255, 0, 0 ) );
		cv::cvtColor( *image, *image, CV_GRAY2BGR );
		bgr.copyTo( *image );
		image->convertTo( *image, CV_8UC3 );
		cv::cvtColor( *image, *image, CV_BGR2BGRA );
	}
	else
	{
		cv::cvtColor( *image, *image, CV_GRAY2BGRA );
	}
	
}

void OpticalFlowFarneback::drawOptFlowMap( const cv::Mat& flow, cv::Mat& cflowmap, int step, double scale, const cv::Scalar& color )
{
	for(int y = 0; y < cflowmap.rows; y += step)
		for(int x = 0; x < cflowmap.cols; x += step)
		{
			const cv::Point2f& fxy = flow.at<cv::Point2f>(y, x);
			const cv::Point2f end = cv::Point( cvRound( x+( fxy.x * scale ) ) , cvRound( y+ ( fxy.y * scale ) ) ) ;
			const cv::Point2f start = cv::Point( x, y) ;
			float length = cv::norm( end - start );
			if( length > minLength && length < maxLength )
			{
				cv::line(cflowmap, start, end, color);
			}
			
			//cv::circle(cflowmap, cv::Point(x,y), 1, color, -1);
		}
}

void OpticalFlowFarneback::setPyrScale( double _pyr_scale )
{
	std::cout << "pyrscale changed." << std::endl;
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

	double polySigma = _polySigma / 100.0;
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
	std::cout << "changed scale: " << _scale << std::endl;
	this->setScale( _scale );
}

void OpticalFlowFarneback::apply( cv::gpu::GpuMat * image )
{
	if( activated )
	{
		//timer.start();
		cv::Mat calcImage( *image );
		this->calc( &calcImage );
		image->upload( calcImage );
		//timer.stop();
		//timer.store();
		//this->calc_GPU( image );
	}
	//std::cout << "FarnebackOpticalFlow took: " << timer.getLatestStdString() << std::endl;
}

void OpticalFlowFarneback::toggleConfigWindow( void )
{
	gui->setVisible( !gui->isVisible() );
}

void OpticalFlowFarneback::activate( void )
{
	activated = !activated;
	std::cout << "farn actrivated now: " << activated << std::endl;
}

void OpticalFlowFarneback::changedMinLength( int _miNlength )
{
	this->minLength = _miNlength;
}

void OpticalFlowFarneback::changedMaxLength( int _maxLength )
{
	this->maxLength = _maxLength;
}

void OpticalFlowFarneback::calc_GPU( cv::gpu::GpuMat * image )
{
	cv::gpu::GpuMat flowX, flowY;
	cv::gpu::GpuMat currentImage;
	cv::gpu::cvtColor( *image, currentImage, CV_BGRA2GRAY );

	if( previousGpuImage.size() != currentImage.size() )
	{
		currentImage.copyTo( previousGpuImage );
	}

	cv::gpu::FarnebackOpticalFlow farn;
	farn( currentImage, previousGpuImage, flowX, flowY );

	currentImage.copyTo( previousGpuImage );

	cv::gpu::cvtColor( currentImage, *image, CV_GRAY2BGRA );
	std::cout << "gpu farneback is working." << std::endl;
}
