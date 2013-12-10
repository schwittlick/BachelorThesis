#pragma once

#include "ProcessingStep.h"

class GradientStep : public ProcessingStep
{
public:
	GradientStep(void);
	~GradientStep(void);

	void apply( cv::gpu::GpuMat * image );
};

