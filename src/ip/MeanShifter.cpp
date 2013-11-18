#include "MeanShifter.h"


MeanShifter::MeanShifter(void)
{
	timers.push_back( Timer() );
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

void MeanShifter::applyMeanShiftFiltering_GPU( cv::Mat * image )
{
	cv::cvtColor( *image, *image, CV_BGR2BGRA );
	gpu_image_src.upload( *image );
	cv::gpu::meanShiftFiltering( gpu_image_src, gpu_image_dst, 20, 20 );
	gpu_image_dst.download( *image );
}

void MeanShifter::applyMeanShiftSegmentation_GPU( cv::Mat * image )
{
	cv::cvtColor( *image, *image, CV_BGR2BGRA );
	gpu_image_src.upload( *image );
	cv::gpu::meanShiftSegmentation(gpu_image_src, *image, 20, 20, 5 );
}

void MeanShifter::pyrMeanShiftFiltering_CPU( cv::Mat * image )
{
	cv::cvtColor( *image, *image, CV_BGR2BGRA );
	cv::pyrMeanShiftFiltering( *image, *image, 20, 20, 5 );
}

void MeanShifter::applyMeanShiftProc_GPU( cv::Mat * image )
{
	std::cout << "TODO -> using specially found points to apply the meanshifting on" << std::endl;
}

double MeanShifter::getAverageElapsedTime( enum Type type )
{
	return timers.at( type ).getAverageTime();
}
