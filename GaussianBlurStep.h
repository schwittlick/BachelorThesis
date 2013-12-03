#pragma once

#include "ProcessingStep.h"


class GaussianBlurStep : public ProcessingStep
{
public:
	GaussianBlurStep(void);
	~GaussianBlurStep(void);

	void apply( cv::gpu::GpuMat * image );
};

