#pragma once

#include <iostream>
#include <vector>

#include "opencv2/core/core.hpp"
#include "opencv2/gpu/gpu.hpp"

#include "src/misc/Timer.h"

/**
 * This is the MeanShifter class, which is utilizing the Mean-shift approach which is a non-parametric feature-space analysis technique, a so-called mode seeking algorithm. 
 * It can be used to help tracking and finding objects in images and image sequences. A small introduction can be found here. http://docs.opencv.org/trunk/doc/py_tutorials/py_video/py_meanshift/py_meanshift.html
*/
class MeanShifter
{
public:
	/**
	* This is the MeanShifter constructor.
	*/
	MeanShifter(void);

	/**
	* This is the MeanShifter destructor.
	*/
	~MeanShifter(void);

	//! the different meanshifter techniques available
	enum Type { FILTERING_GPU, SEGMENTATION_GPU, FILTERING_CPU, PROC };

	//! actually applies a meanshift filter technique on the passed image pointer with the technique indicated by type
	//! @param image a pointer to the image, on which the meanshift is going to be applied on. 
	//! @param type the type of meanshifting which is going to be applied
	void applyMeanShift( cv::Mat * image, enum Type type );

	//! this apploes a meanshift filter on the passed cv::gpu::GpuMat with the selected meanshift-type.
	//! by passind a cv::gpu::GpuMat the image data doesn't need to be down-/uploaded to/from the host to process it. this makes the
	//! entire process a lot faster.
	//! @param gpu_image a pointer to the image to be processed. it _NEEDS_ to be in BGRA/CV_8UC4 format. check the opencv documentation for this issue: http://docs.opencv.org/modules/gpu/doc/image_processing.html
	void applyMeanShiftFilteringGpuOnly( cv::gpu::GpuMat * gpu_image );

	//! a benchmark function. it returns the amount of milliseconds a technique took to compute. the type of which the benchmark is returned is indicated by the passed parameter
	//! @param type indicates the type of meanshift you want the elapsed time benchmark of
	//! @return the time each processing of the meanshift took in average in milliseconds
	double getAverageElapsedTime( enum Type type );

	//! sets the spacial window radius
	//! @param _spacialWindowRadius the new spacial window radius being used
	void setSpacialWindowRadius( int _spacialWindowRadius );

	//! sets the color window radius
	//! @param _colorWindowRadius the new color window radius being used
	void setColorWindowRadius( int _colorWindowRadius );

	//! sets the minimum segment size 
	//! @param _minimumSegmentSize the new minimum size of segments being used
	void setMinimumSegmentSize( int _minimumSegmentSize );

	//! @return the spacial window radius currently being used
	int getSpacialWindowRadius( void );

	//! @return the color window radius currently being used
	int getColorWindowRadius( void );

	//! @return the minimum segment size currently being used.
	int getMinimumSegmentSize( void );

private:
	//! vector holding the different timers to benchmark the different types of mean shifts
	std::vector< Timer > timers;

	//! global gpu mats, which are necessary to compute gpu methods, since they need to be uploaded to the gpu
	cv::gpu::GpuMat gpu_image_src, gpu_image_dst;


	int spacialWindowRadius, colorWindowRadius;
	
	//! only being applied with MeanShifter::Type::SEGMENTATION_GPU. smaller segments are merged.
	int minimumSegmentSize;

	//! uses meanShiftFiltering on the GPU
	//! @param image a pointer to the image, on which the meanshift is going to be applied on. 
	void applyMeanShiftFiltering_GPU( cv::Mat * image );

	//! uses meanShiftSegmentation on the GPU
	//! @param image a pointer to the image, on which the meanshift is going to be applied on. 
	void applyMeanShiftSegmentation_GPU( cv::Mat * image );

	//! uses pyrMeanShiftFilterin on the CPU
	//! @param image a pointer to the image, on which the meanshift is going to be applied on. 
	void pyrMeanShiftFiltering_CPU( cv::Mat * image );

	//! creates a meanShift procedure only being applied to certain points
	//! @param image a pointer to the image, on which the meanshift is going to be applied on. 
	void applyMeanShiftProc_GPU( cv::Mat * image );
};

