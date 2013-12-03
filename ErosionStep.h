#pragma once

#include "ProcessingStep.h"

class ErosionStep : public ProcessingStep
{
public:
	ErosionStep(void);
	~ErosionStep(void);

	void apply( cv::gpu::GpuMat * image );
};

