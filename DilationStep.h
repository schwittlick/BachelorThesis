#pragma once

#include "ProcessingStep.h"

class DilationStep : public ProcessingStep
{
public:
	DilationStep(void);
	~DilationStep(void);

	void apply( cv::gpu::GpuMat * image );
};

