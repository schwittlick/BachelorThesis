#include "StandardImageProcessor.h"


StandardImageProcessor::StandardImageProcessor(void) :
	kernelSize( 3 )
{
	setKernelSize( kernelSize );
}


StandardImageProcessor::~StandardImageProcessor(void)
{
}

void StandardImageProcessor::open( cv::gpu::GpuMat * image )
{
	cv::gpu::morphologyEx( *image, *image, cv::MORPH_OPEN, kernel, cv::Point( -1, -1 ), 1 );
}

void StandardImageProcessor::open( cv::gpu::GpuMat * image, int iterations )
{
	cv::gpu::morphologyEx( *image, *image, cv::MORPH_OPEN, kernel, cv::Point( -1, -1 ), iterations );
}

void StandardImageProcessor::close( cv::gpu::GpuMat * image )
{
	cv::gpu::morphologyEx( *image, *image, cv::MORPH_CLOSE, kernel, cv::Point( -1, -1 ), 1 );
}

void StandardImageProcessor::close( cv::gpu::GpuMat * image, int iterations )
{
	cv::gpu::morphologyEx( *image, *image, cv::MORPH_CLOSE, kernel, cv::Point( -1, -1 ), iterations );
}

void StandardImageProcessor::dilate( cv::gpu::GpuMat * image )
{
	cv::Mat tmp;
	image->download( tmp );
	cv::dilate( tmp, tmp, kernel, cv::Point( -1, -1 ), 1, 1, 1 );
	image->upload( tmp );
	//cv::gpu::dilate( *image, *image, kernel, cv::Point( -1, -1 ), 1 );
}

void StandardImageProcessor::dilate( cv::gpu::GpuMat * image, int iterations )
{
	cv::Mat tmp;
	image->download( tmp );
	for( int i = 0; i < iterations; i++ )
	{
		cv::dilate( tmp, tmp, kernel, cv::Point( -1, -1 ), 1, 1, 1 );
	}
	image->upload( tmp );
	//cv::gpu::dilate( *image, *image, kernel, cv::Point( -1, -1 ), iterations );
}

void StandardImageProcessor::erode( cv::gpu::GpuMat * image )
{
	cv::Mat tmp;
	image->download( tmp );
	cv::erode( tmp, tmp, kernel, cv::Point( -1, -1 ), 1, 1, 1 );
	image->upload( tmp );
	//cv::gpu::erode( *image, *image, cv::Mat(), cv::Point( -1, -1 ), 1 );
}

void StandardImageProcessor::erode( cv::gpu::GpuMat * image, int iterations )
{
	cv::Mat tmp;
	image->download( tmp );
	for( int i = 0; i < iterations; i++ )
	{
		cv::erode( tmp, tmp, kernel, cv::Point( -1, -1 ), 1, 1, 1 );
	}
	image->upload( tmp );
	//cv::gpu::erode( *image, *image, kernel, cv::Point( -1, -1 ), iterations );
}

void StandardImageProcessor::gradient( cv::gpu::GpuMat * image )
{
	cv::Mat tmp;
	image->download( tmp );
	cv::morphologyEx( tmp, tmp, CV_MOP_GRADIENT, kernel, cv::Point( kernelSize, kernelSize ), 1 );
	image->upload( tmp );
	//cv::gpu::morphologyEx( *image, *image, cv::MORPH_GRADIENT, kernel, cv::Point( -1, -1 ), 1 );
}

void StandardImageProcessor::gradient( cv::gpu::GpuMat * image, int iterations )
{
	cv::Mat tmp;
	image->download( tmp );
	cv::morphologyEx( tmp, tmp, CV_MOP_GRADIENT, kernel, cv::Point( kernelSize, kernelSize ), iterations );
	image->upload( tmp );
	//cv::gpu::morphologyEx( *image, *image, cv::MORPH_GRADIENT, kernel, cv::Point( -1, -1 ), iterations );
}

void StandardImageProcessor::blackHat( cv::gpu::GpuMat * image )
{
	cv::Mat tmp;
	image->download( tmp );
	cv::morphologyEx( tmp, tmp, CV_MOP_BLACKHAT, kernel, cv::Point( kernelSize, kernelSize ), 1 );
	image->upload( tmp );
	//cv::gpu::morphologyEx( *image, *image, cv::MORPH_BLACKHAT, kernel, cv::Point( -1, -1 ), 1 );
}

void StandardImageProcessor::blackHat( cv::gpu::GpuMat * image, int iterations )
{
	cv::Mat tmp;
	image->download( tmp );
	cv::morphologyEx( tmp, tmp, CV_MOP_BLACKHAT, kernel, cv::Point( kernelSize, kernelSize ), iterations );
	image->upload( tmp );
	//cv::gpu::morphologyEx( *image, *image, cv::MORPH_BLACKHAT, kernel, cv::Point( -1, -1 ), iterations );
}

void StandardImageProcessor::binary( cv::gpu::GpuMat * image, int threshold )
{	
	cv::gpu::GpuMat tmpMat;
	cv::gpu::cvtColor( *image, tmpMat, CV_BGRA2GRAY );
	cv::gpu::threshold( tmpMat, tmpMat, threshold, 255, 0 );
	cv::gpu::cvtColor( tmpMat, *image, CV_GRAY2BGRA );
}

void StandardImageProcessor::topHat( cv::gpu::GpuMat * image, int iterations )
{
	cv::Mat tmp;
	image->download( tmp );
	cv::morphologyEx( tmp, tmp, CV_MOP_TOPHAT, kernel, cv::Point( kernelSize, kernelSize ), iterations );
	image->upload( tmp );
	//cv::gpu::morphologyEx( *image, *image, cv::MORPH_TOPHAT, kernel, cv::Point( -1, -1 ), iterations );
}

void StandardImageProcessor::topHat( cv::gpu::GpuMat * image )
{
	cv::Mat tmp;
	image->download( tmp );
	cv::morphologyEx( tmp, tmp, CV_MOP_TOPHAT, kernel, cv::Point( kernelSize, kernelSize ), 1 );
	image->upload( tmp );
	//cv::gpu::morphologyEx( *image, *image, cv::MORPH_BLACKHAT, kernel, cv::Point( -1, -1 ), 1 );
}

void StandardImageProcessor::setKernelSize( int _kernelSize )
{
	this->kernelSize = _kernelSize;
	kernel = cv::getStructuringElement( 0, cv::Size( 2 * kernelSize + 1, 2 * kernelSize + 1 ), cv::Point( kernelSize, kernelSize ) );
}
