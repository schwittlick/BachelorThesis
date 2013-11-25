#include "DualTVL1OpticalFlow.h"


DualTVL1OpticalFlow::DualTVL1OpticalFlow(void) :
	firstTime( true ),
	gpuFrame0( cv::Size( 576, 720 ), CV_8UC1 ),
	gpuFrame1( cv::Size( 576, 720 ), CV_8UC1 ),
	gpuFlowX( cv::Size( 576, 720 ), CV_32FC1 ),
	gpuFlowY( cv::Size( 576, 720 ), CV_32FC1 ),
	cpuFlow( cv::Size( 576, 720 ), CV_8UC4 ),
	gpuFlow( cv::Size( 576, 720 ), CV_8UC4 ),
	cpuFlowX( cv::Size( 576, 720 ), CV_8UC4 ),
	cpuFlowY( cv::Size( 576, 720 ), CV_8UC4 )
{
	dualTvli1 = cv::createOptFlow_DualTVL1();
	const std::string name = "DualTVL1";

}


DualTVL1OpticalFlow::~DualTVL1OpticalFlow(void)
{
}

cv::gpu::GpuMat DualTVL1OpticalFlow::calcGPU( cv::gpu::GpuMat * _gpu_image )
{
	cv::gpu::GpuMat gray_gpu_image;
	cv::gpu::cvtColor( *_gpu_image, gray_gpu_image, CV_BGRA2GRAY );
	
	if( firstTime )
	{
		gpuFrame0 = gray_gpu_image.clone();
		firstTime = false;
	}

	gpuFrame1 = gray_gpu_image.clone();

	tvl1( gpuFrame0, gpuFrame1, gpuFlowX, gpuFlowY );

	gpuFrame0 = gpuFrame1.clone();

	gpuFlowX.download( cpuFlowX );
	gpuFlowY.download( cpuFlowY );
	drawOpticalFlow( cpuFlowX, cpuFlowY, cpuFlow, -1 );
	gpuFlow.upload( cpuFlow );
	
	return gpuFlow;
}

cv::Mat DualTVL1OpticalFlow::calc( cv::Mat * _image )
{
	cv::cvtColor( *_image, *_image, CV_BGRA2GRAY );
	std::cout << "Current type: " << _image->type() << std::endl;
	std::cout << "previous type:" << previousMat.type() << std::endl;
	if( firstTime )
	{
		_image->copyTo( previousMat );
		firstTime = false;
	}

	cv::Mat returnMat = cv::Mat::zeros( 576, 720, CV_8UC4 );
	dualTvli1->calc( previousMat, *_image, returnMat );

	_image->copyTo( previousMat );

	cv::cvtColor( *_image, *_image, CV_GRAY2BGRA );

	std::cout << "returnMat type: " << returnMat.type() << std::endl;

	cv::Mat xy[2]; //X,Y
	cv::split(returnMat, xy);

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

	std::cout << "bgr type: " << bgr.type() << std::endl;
	

	return bgr;
}

double DualTVL1OpticalFlow::getTau( void )
{
	double tau = dualTvli1->getDouble( "tau" );
	return tau;
}

void DualTVL1OpticalFlow::setTau( double _tau )
{
	dualTvli1->setDouble( "tau", _tau );
	tvl1.tau = _tau;
}

double DualTVL1OpticalFlow::getLambda( void )
{
	double lambda = dualTvli1->getDouble( "lambda" );
	return lambda;
}

void DualTVL1OpticalFlow::setLambda( double _lambda )
{
	dualTvli1->setDouble( "lambda", _lambda );
	tvl1.lambda = _lambda;
}

double DualTVL1OpticalFlow::getTheta( void )
{
	double theta = dualTvli1->getDouble( "theta" );
	return theta;
}

void DualTVL1OpticalFlow::setTheta( double _theta )
{
	dualTvli1->setDouble( "theta", _theta );
	tvl1.theta = _theta;
}

int DualTVL1OpticalFlow::getNScales( void )
{
	int nscales = dualTvli1->getInt( "nscales" );
	return nscales;
}

void DualTVL1OpticalFlow::setNScales( int _nscales )
{
	dualTvli1->setInt( "nscales", _nscales );
	tvl1.nscales = _nscales;
}

int DualTVL1OpticalFlow::getWarps( void )
{
	int warps = dualTvli1->getInt( "warps" );
	return warps;
}

void DualTVL1OpticalFlow::setWarps( int _warps )
{
	dualTvli1->setInt( "warps", _warps );
	tvl1.warps = _warps;
}

double DualTVL1OpticalFlow::getEpsilon( void )
{
	double epsilon = dualTvli1->getDouble( "epsilon" );
	return epsilon;
}

void DualTVL1OpticalFlow::setEpsilon( double _epsilon )
{
	dualTvli1->setDouble( "epsilon", _epsilon );
	tvl1.epsilon = _epsilon;
}

int DualTVL1OpticalFlow::getIterations( void )
{
	int iterations = dualTvli1->getInt( "iterations" );
	return iterations;
}

void DualTVL1OpticalFlow::setIterations( int _iterations )
{
	dualTvli1->setInt( "iterations", _iterations );
	tvl1.iterations = _iterations;
}

void DualTVL1OpticalFlow::drawOpticalFlow( const cv::Mat_<float>& flowx, const cv::Mat_<float>& flowy, cv::Mat& dst, float maxmotion /*= -1*/ )
{
	dst.create(flowx.size(), CV_8UC3);
	dst.setTo(cv::Scalar::all(0));

	// determine motion range:
	float maxrad = maxmotion;

	if (maxmotion <= 0)
	{
		maxrad = 1;
		for (int y = 0; y < flowx.rows; ++y)
		{
			for (int x = 0; x < flowx.cols; ++x)
			{
				cv::Point2f u(flowx(y, x), flowy(y, x));

				if (!isFlowCorrect(u))
					continue;

				maxrad = cv::max(maxrad, sqrt(u.x * u.x + u.y * u.y));
			}
		}
	}

	for (int y = 0; y < flowx.rows; ++y)
	{
		for (int x = 0; x < flowx.cols; ++x)
		{
			cv::Point2f u(flowx(y, x), flowy(y, x));

			if ( isFlowCorrect( u ) )
				dst.at< cv::Vec3b >( y, x ) = computeColor( u.x / maxrad, u.y / maxrad );
		}
	}

}

bool DualTVL1OpticalFlow::isFlowCorrect( cv::Point2f u )
{
	 return !cvIsNaN(u.x) && !cvIsNaN(u.y) && fabs(u.x) < 1e9 && fabs(u.y) < 1e9;
}

cv::Vec3b DualTVL1OpticalFlow::computeColor( float fx, float fy )
{
	static bool first = true;

	// relative lengths of color transitions:
	// these are chosen based on perceptual similarity
	// (e.g. one can distinguish more shades between red and yellow
	//  than between yellow and green)
	const int RY = 15;
	const int YG = 6;
	const int GC = 4;
	const int CB = 11;
	const int BM = 13;
	const int MR = 6;
	const int NCOLS = RY + YG + GC + CB + BM + MR;
	static cv::Vec3i colorWheel[NCOLS];

	if (first)
	{
		int k = 0;

		for (int i = 0; i < RY; ++i, ++k)
			colorWheel[k] = cv::Vec3i(255, 255 * i / RY, 0);

		for (int i = 0; i < YG; ++i, ++k)
			colorWheel[k] = cv::Vec3i(255 - 255 * i / YG, 255, 0);

		for (int i = 0; i < GC; ++i, ++k)
			colorWheel[k] = cv::Vec3i(0, 255, 255 * i / GC);

		for (int i = 0; i < CB; ++i, ++k)
			colorWheel[k] = cv::Vec3i(0, 255 - 255 * i / CB, 255);

		for (int i = 0; i < BM; ++i, ++k)
			colorWheel[k] = cv::Vec3i(255 * i / BM, 0, 255);

		for (int i = 0; i < MR; ++i, ++k)
			colorWheel[k] = cv::Vec3i(255, 0, 255 - 255 * i / MR);

		first = false;
	}

	const float rad = sqrt(fx * fx + fy * fy);
	const float a = atan2(-fy, -fx) / (float) CV_PI;

	const float fk = (a + 1.0f) / 2.0f * (NCOLS - 1);
	const int k0 = static_cast<int>(fk);
	const int k1 = (k0 + 1) % NCOLS;
	const float f = fk - k0;

	cv::Vec3b pix;

	for (int b = 0; b < 3; b++)
	{
		const float col0 = colorWheel[k0][b] / 255.0f;
		const float col1 = colorWheel[k1][b] / 255.0f;

		float col = (1 - f) * col0 + f * col1;

		if (rad <= 1)
			col = 1 - rad * (1 - col); // increase saturation with radius
		else
			col *= .75; // out of range

		pix[2 - b] = static_cast<uchar>(255.0 * col);
	}

	return pix;
}
