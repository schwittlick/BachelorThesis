#include "OpticalFlowFarneback.h"


OpticalFlowFarneback::OpticalFlowFarneback(void)
{
	previousImage = cv::Mat::zeros( 576, 720, CV_8UC1 );
}


OpticalFlowFarneback::~OpticalFlowFarneback(void)
{
}

std::vector< cv::Point > OpticalFlowFarneback::calc( cv::Mat * image )
{
	//cv::calcOpticalFlowPyrLK( previousImage, *image, , )
	std::cout << "Started FarnebackOpticalFlow." << std::endl;
	std::vector< cv::Point > poitsn;

	std::cout << "Original Type of to copy to " << image->type() << std::endl;

	cv::cvtColor( *image, *image, CV_BGRA2GRAY);

	cv::Mat outputImage;
	cv::calcOpticalFlowFarneback(previousImage, *image, outputImage, 0.5, 3, 15, 3, 5, 1.2, 0 );
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

	drawOptFlowMap( outputImage, bgr, 15, 20.0, cv::Scalar( 255, 0, 0 ) );

	bgr.copyTo( *image );

	return poitsn;
}

void OpticalFlowFarneback::drawOptFlowMap( const cv::Mat& flow, cv::Mat& cflowmap, int step, double scale, const cv::Scalar& color )
{
	for(int y = 0; y < cflowmap.rows; y += step)
		for(int x = 0; x < cflowmap.cols; x += step)
		{
			const cv::Point2f& fxy = flow.at<cv::Point2f>(y, x);
			line(cflowmap, cv::Point(x,y), cv::Point(cvRound(x+fxy.x), cvRound(y+fxy.y)),
				color);
			cv::circle(cflowmap, cv::Point(x,y), 2, color, -1);
		}
}
