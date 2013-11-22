#include "MeanShifter.h"


MeanShifter::MeanShifter(void) :
	spacialWindowRadius( 20 ),
	colorWindowRadius( 20 ),
	minimumSegmentSize( 5 )
{
	for( int i = 0; i < 4; i++ ) 
	{
		timers.push_back( Timer() );
	}
}


MeanShifter::~MeanShifter(void)
{
}

void MeanShifter::applyMeanShift( cv::Mat * image, enum Type type )
{
	switch( type )
	{
	case Type::FILTERING_CPU:
		timers.at( Type::FILTERING_CPU ).start();
		pyrMeanShiftFiltering_CPU( image );
		timers.at( Type::FILTERING_CPU ).stop();
		timers.at( Type::FILTERING_CPU ).store();
		break;
	case Type::FILTERING_GPU:
		timers.at( Type::FILTERING_GPU ).start();
		applyMeanShiftFiltering_GPU( image );
		timers.at( Type::FILTERING_GPU ).start();
		timers.at( Type::FILTERING_GPU ).start();
		break;
	case Type::PROC:
		timers.at( Type::PROC ).start();
		applyMeanShiftProc_GPU( image );
		timers.at( Type::PROC ).start();
		timers.at( Type::PROC ).start();
		break;
	case Type::SEGMENTATION_GPU:
		timers.at( Type::SEGMENTATION_GPU ).start();
		applyMeanShiftSegmentation_GPU( image );
		timers.at( Type::SEGMENTATION_GPU ).start();
		timers.at( Type::SEGMENTATION_GPU ).start();
		break;
	}
}

void MeanShifter::applyMeanShiftFilteringGpuOnly( cv::gpu::GpuMat * gpu_image )
{
	if( gpu_image->type() == CV_8UC4 )
	{
		cv::gpu::meanShiftFiltering( * gpu_image, *gpu_image, spacialWindowRadius, colorWindowRadius );
	}
	else
	{
		std::cerr << "The cv::gpu::GpuMat.type() needs to be CV_8UC4." << std::endl;
		// TODO: throw some sort of exception when this happens
	}
}

void MeanShifter::applyMeanShiftFiltering_GPU( cv::Mat * image )
{
	cv::cvtColor( *image, *image, CV_BGR2BGRA );
	gpu_image_src.upload( *image );
	cv::gpu::meanShiftFiltering( gpu_image_src, gpu_image_dst, spacialWindowRadius, colorWindowRadius );
	gpu_image_dst.download( *image );
}

void MeanShifter::applyMeanShiftSegmentation_GPU( cv::Mat * image )
{
	cv::cvtColor( *image, *image, CV_BGR2BGRA );
	gpu_image_src.upload( *image );
	cv::gpu::meanShiftSegmentation(gpu_image_src, *image, spacialWindowRadius, colorWindowRadius, minimumSegmentSize );
}

void MeanShifter::pyrMeanShiftFiltering_CPU( cv::Mat * image )
{
	cv::cvtColor( *image, *image, CV_BGR2BGRA );
	cv::pyrMeanShiftFiltering( *image, *image, spacialWindowRadius, colorWindowRadius, minimumSegmentSize );
}

void MeanShifter::applyMeanShiftProc_GPU( cv::Mat * image )
{
	std::cout << "TODO -> using specially found points to apply the meanshifting on" << std::endl;
}

double MeanShifter::getAverageElapsedTime( enum Type type )
{
	return timers.at( type ).getAverageTime();
}

void MeanShifter::setSpacialWindowRadius( int _spacialWindowRadius )
{
	this->spacialWindowRadius = _spacialWindowRadius;
}

void MeanShifter::setColorWindowRadius( int _colorWindowRadius )
{
	this->colorWindowRadius = _colorWindowRadius;
}

void MeanShifter::setMinimumSegmentSize( int _minimumSegmentSize )
{
	this->minimumSegmentSize = _minimumSegmentSize;
}

int MeanShifter::getSpacialWindowRadius( void )
{
	return spacialWindowRadius;
}

int MeanShifter::getColorWindowRadius( void )
{
	return colorWindowRadius;
}

int MeanShifter::getMinimumSegmentSize( void )
{
	return minimumSegmentSize;
}
