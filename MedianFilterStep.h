#pragma once

#include "ProcessingStep.h"

class MedianFilterStep : public ProcessingStep
{
public:
	MedianFilterStep(void);
	~MedianFilterStep(void);

	void apply( cv::gpu::GpuMat * image );
};

