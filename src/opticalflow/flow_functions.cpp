
//=============================================================================
//
// flow_functions.cpp
// Functions for dense optical flow visualization
// Author: Pablo F. Alcantarilla
// Institution: ALCoV, Université d'Auvergne
// Date: 14/06/2012
// Email: pablofdezalc@gmail.com
//=============================================================================

#include "flow_functions.h"

// Namespaces
using namespace std;
using namespace cv;

//******************************************************************************
//******************************************************************************

/** This function calculates rgb values from hsv color space                     */
void hsv2rgb(float h, float s, float v, unsigned char &r, unsigned char &g, unsigned char &b)
{
	float c = 0.0, hp = 0.0, hpmod2 = 0.0, x = 0.0;
	float m = 0.0, r1 = 0.0, g1 = 0.0, b1 = 0.0;

	if(h > 360)
	{
		h = h - 360;
	}

	c = v*s;   // chroma
	hp = h / 60;
	hpmod2 = hp - (float)((int)(hp/2))*2;

	x = c*(1 - fabs(hpmod2 - 1));
	m = v - c;

	if(0 <= hp && hp < 1)
	{
		r1 = c;
		g1 = x;
		b1 = 0;
	}
	else if(1 <= hp && hp < 2)
	{
		r1 = x;
		g1 = c;
		b1 = 0;
	}
	else if(2 <= hp && hp < 3)
	{
		r1 = 0;
		g1 = c;
		b1 = x;
	}
	else if(3 <= hp && hp < 4)
	{
		r1 = 0;
		g1 = x;
		b1 = c;
	}
	else if(4 <= hp && hp < 5)
	{
		r1 = x;
		g1 = 0;
		b1 = c;
	}
	else
	{
		r1 = c;
		g1 = 0;
		b1 = x;
	}

	r = (unsigned char)(255*(r1 + m));
	g = (unsigned char)(255*(g1 + m));
	b = (unsigned char)(255*(b1 + m));
}

//******************************************************************************
//******************************************************************************

/** This function draws a vector field based on horizontal and vertical flow fields   */
void drawMotionField(Mat &imgU, Mat &imgV, Mat &imgMotion,
					 int xSpace, int ySpace, float minCutoff, float maxCutoff, float multiplier, CvScalar color)
{
	int x = 0, y = 0;
	float *ptri;
	float deltaX = 0.0, deltaY = 0.0, angle = 0.0, hyp = 0.0;
	Point p0, p1;

	for( y = ySpace; y < imgU.rows; y += ySpace )
	{
		for(x = xSpace; x < imgU.cols; x += xSpace )
		{
			p0.x = x;
			p0.y = y;

			ptri = imgU.ptr<float>(y);
			deltaX = ptri[x];

			ptri = imgV.ptr<float>(y);
			deltaY = ptri[x];

			angle = atan2(deltaY, deltaX);
			hyp = sqrt(deltaX*deltaX + deltaY*deltaY);

			if( hyp > minCutoff && hyp < maxCutoff )
			{
				p1.x = p0.x + cvRound(multiplier*hyp*cos(angle));
				p1.y = p0.y + cvRound(multiplier*hyp*sin(angle));

				cv::line(imgMotion,p0,p1,color,1,CV_AA,0);

				/*
				p0.x = p1.x + cvRound(2*cos(angle-M_PI + M_PI/4));
				p0.y = p1.y + cvRound(2*sin(angle-M_PI + M_PI/4));
				cv::line( imgMotion, p0, p1, color,1, CV_AA, 0);

				p0.x = p1.x + cvRound(2*cos(angle-M_PI - M_PI/4));
				p0.y = p1.y + cvRound(2*sin(angle-M_PI - M_PI/4));
				cv::line( imgMotion, p0, p1, color,1, CV_AA, 0);
				*/
			}
		}
	}
}

/** This function draws a vector field based on horizontal and vertical flow fields   */
void drawMotionField_GPU(cv::gpu::GpuMat &imgU, cv::gpu::GpuMat &imgV, cv::gpu::GpuMat &imgMotion,
					 int xSpace, int ySpace, float minCutoff, float maxCutoff, float multiplier, CvScalar color)
{
	cv::Mat drawMat(cv::Size( imgU.size().width, imgU.size().height), CV_8UC3 );
	int x = 0, y = 0;
	float *ptri;
	float deltaX = 0.0, deltaY = 0.0, angle = 0.0, hyp = 0.0;
	Point p0, p1;

	for( y = ySpace; y < imgU.rows; y += ySpace )
	{
		for(x = xSpace; x < imgU.cols; x += xSpace )
		{
			p0.x = x;
			p0.y = y;

			ptri = imgU.ptr<float>(y);
			deltaX = ptri[x];

			ptri = imgV.ptr<float>(y);
			deltaY = ptri[x];

			angle = atan2(deltaY, deltaX);
			hyp = sqrt(deltaX*deltaX + deltaY*deltaY);

			if( hyp > minCutoff && hyp < maxCutoff )
			{
				p1.x = p0.x + cvRound(multiplier*hyp*cos(angle));
				p1.y = p0.y + cvRound(multiplier*hyp*sin(angle));

				cv::line(drawMat,p0,p1,color,1,CV_AA,0);

				/*
				p0.x = p1.x + cvRound(2*cos(angle-M_PI + M_PI/4));
				p0.y = p1.y + cvRound(2*sin(angle-M_PI + M_PI/4));
				cv::line( imgMotion, p0, p1, color,1, CV_AA, 0);

				p0.x = p1.x + cvRound(2*cos(angle-M_PI - M_PI/4));
				p0.y = p1.y + cvRound(2*sin(angle-M_PI - M_PI/4));
				cv::line( imgMotion, p0, p1, color,1, CV_AA, 0);
				*/
			}
		}
	}

	imgMotion.upload( drawMat );
}

//******************************************************************************
//******************************************************************************

/** Draws the circular legend for the color field, indicating direction and magnitude */
void drawLegendHSV(Mat &imgColor, int radius, int px, int py)
{
	unsigned char *legend_ptr, *img_ptr;
	float angle = 0.0, h = 0.0, s = 0.0, v = 0.0, legend_max_s = 0.0;
	unsigned char r = 0, g = 0, b = 0;
	int deltaX = 0, deltaY = 0, mod = 0;
	int width = radius*2 + 1;
	int height = width;

	Mat imgLegend = cv::Mat::zeros(Size(width,height),CV_8UC3);

	legend_max_s = radius*sqrt(2);

	for( int y = 0; y < imgLegend.rows; y++ )
	{
		legend_ptr = imgLegend.ptr<unsigned char>(y);

		for( int x = 0; x < imgLegend.cols; x++ )
		{
			deltaX = x-radius;
			deltaY = -(y-radius);
			angle = atan2(deltaY,deltaX);

			if( angle < 0.0 )
			{
				angle += 2*M_PI;
			}

			h = angle * 180.0 / M_PI;
			s = sqrt(deltaX*deltaX + deltaY*deltaY) / legend_max_s;
			v = 0.9;

			hsv2rgb(h,s,v,r,g,b);

			legend_ptr[3*x] = b;
			legend_ptr[3*x+1] = g;
			legend_ptr[3*x+2] = r;

			mod = (x-radius)*(x-radius) + (y-radius)*(y-radius);

			if(  mod < radius*radius )
			{
				img_ptr = imgColor.ptr<unsigned char>(py+y);
				img_ptr[3*(px+x)] = legend_ptr[3*x];
				img_ptr[3*(px+x)+1] = legend_ptr[3*x+1];
				img_ptr[3*(px+x)+2] = legend_ptr[3*x+2];
			}
		}
	}

	// Draw a black circle over the legend
	cv::circle(imgColor,cv::Point(px+radius,py+radius),radius,CV_RGB(0,0,0),2,8,0);
}

void drawLegendHSV(cv::gpu::GpuMat &imgColor, int radius, int px, int py)
{
	unsigned char *legend_ptr, *img_ptr;
	float angle = 0.0, h = 0.0, s = 0.0, v = 0.0, legend_max_s = 0.0;
	unsigned char r = 0, g = 0, b = 0;
	int deltaX = 0, deltaY = 0, mod = 0;
	int width = radius*2 + 1;
	int height = width;

	Mat imgLegend = cv::Mat::zeros(Size(width,height),CV_8UC3);

	legend_max_s = radius*sqrt(2);

	for( int y = 0; y < imgLegend.rows; y++ )
	{
		legend_ptr = imgLegend.ptr<unsigned char>(y);

		for( int x = 0; x < imgLegend.cols; x++ )
		{
			deltaX = x-radius;
			deltaY = -(y-radius);
			angle = atan2(deltaY,deltaX);

			if( angle < 0.0 )
			{
				angle += 2*M_PI;
			}

			h = angle * 180.0 / M_PI;
			s = sqrt(deltaX*deltaX + deltaY*deltaY) / legend_max_s;
			v = 0.9;

			hsv2rgb(h,s,v,r,g,b);

			legend_ptr[3*x] = b;
			legend_ptr[3*x+1] = g;
			legend_ptr[3*x+2] = r;

			mod = (x-radius)*(x-radius) + (y-radius)*(y-radius);

			if(  mod < radius*radius )
			{
				img_ptr = imgColor.ptr<unsigned char>(py+y);
				img_ptr[3*(px+x)] = legend_ptr[3*x];
				img_ptr[3*(px+x)+1] = legend_ptr[3*x+1];
				img_ptr[3*(px+x)+2] = legend_ptr[3*x+2];
			}
		}
	}

	// Draw a black circle over the legend
	//cv::circle(imgColor,cv::Point(px+radius,py+radius),radius,CV_RGB(0,0,0),2,8,0);
	//cv::gpu::ci
}

//******************************************************************************
//******************************************************************************

/** This function draws a color field representation of the flow field          */
void drawColorField(Mat &imgU, Mat &imgV, Mat &imgColor)
{
	Mat imgColorHSV = cv::Mat::zeros(Size(imgColor.cols,imgColor.rows),CV_32FC3);

	float max_s = 0;
	float *hsv_ptr, *u_ptr, *v_ptr;
	unsigned char *color_ptr;
	unsigned char r = 0, g = 0, b = 0;
	float angle = 0.0;
	float h = 0.0, s = 0.0, v = 0.0;
	float deltaX = 0.0, deltaY = 0.0;
	int x = 0, y = 0;

	// Generate hsv image
	for( y = 0; y < imgColor.rows; y++ )
	{
		hsv_ptr = imgColorHSV.ptr<float>(y);
		u_ptr = imgU.ptr<float>(y);
		v_ptr = imgV.ptr<float>(y);

		for( x = 0; x < imgColorHSV.cols; x++)
		{
			deltaX = u_ptr[x];
			deltaY = -v_ptr[x];
			angle = atan2(deltaY,deltaX);

			if( angle < 0)
			{
				angle += 2*M_PI;
			}

			hsv_ptr[3*x] = angle * 180 / M_PI;
			hsv_ptr[3*x+1] = sqrt(deltaX*deltaX + deltaY*deltaY);
			hsv_ptr[3*x+2] = 0.9;

			if( hsv_ptr[3*x+1] > max_s )
			{
				max_s = hsv_ptr[3*x+1];
			}
		}
	}

	// Generate color image
	for(y = 0; y < imgColor.rows; y++ )
	{
		hsv_ptr = imgColorHSV.ptr<float>(y);
		color_ptr = imgColor.ptr<unsigned char>(y);

		for( x = 0; x < imgColor.cols; x++)
		{
			h = hsv_ptr[3*x];
			s = hsv_ptr[3*x+1] / max_s;
			v = hsv_ptr[3*x+2];

			hsv2rgb(h,s,v,r,g,b);

			color_ptr[3*x] = b;
			color_ptr[3*x+1] = g;
			color_ptr[3*x+2] = r;
		}
	}

	//drawLegendHSV(imgColor,15,25,15);
}

void drawColorField_GPU(cv::gpu::GpuMat &imgU, cv::gpu::GpuMat &imgV, cv::gpu::GpuMat &imgColor)
{
	Mat imgColorHSV = cv::Mat::zeros(Size(imgColor.cols,imgColor.rows),CV_32FC3);

	float max_s = 0;
	float *hsv_ptr, *u_ptr, *v_ptr;
	unsigned char *color_ptr;
	unsigned char r = 0, g = 0, b = 0;
	float angle = 0.0;
	float h = 0.0, s = 0.0, v = 0.0;
	float deltaX = 0.0, deltaY = 0.0;
	int x = 0, y = 0;

	// Generate hsv image
	for( y = 0; y < imgColor.rows; y++ )
	{
		hsv_ptr = imgColorHSV.ptr<float>(y);
		u_ptr = imgU.ptr<float>(y);
		v_ptr = imgV.ptr<float>(y);

		for( x = 0; x < imgColorHSV.cols; x++)
		{
			deltaX = u_ptr[x];
			deltaY = -v_ptr[x];
			angle = atan2(deltaY,deltaX);

			if( angle < 0)
			{
				angle += 2*M_PI;
			}

			hsv_ptr[3*x] = angle * 180 / M_PI;
			hsv_ptr[3*x+1] = sqrt(deltaX*deltaX + deltaY*deltaY);
			hsv_ptr[3*x+2] = 0.9;

			if( hsv_ptr[3*x+1] > max_s )
			{
				max_s = hsv_ptr[3*x+1];
			}
		}
	}

	// Generate color image
	for(y = 0; y < imgColor.rows; y++ )
	{
		hsv_ptr = imgColorHSV.ptr<float>(y);
		color_ptr = imgColor.ptr<unsigned char>(y);

		for( x = 0; x < imgColor.cols; x++)
		{
			h = hsv_ptr[3*x];
			s = hsv_ptr[3*x+1] / max_s;
			v = hsv_ptr[3*x+2];

			hsv2rgb(h,s,v,r,g,b);

			color_ptr[3*x] = b;
			color_ptr[3*x+1] = g;
			color_ptr[3*x+2] = r;
		}
	}

	drawLegendHSV(imgColor,15,25,15);
}