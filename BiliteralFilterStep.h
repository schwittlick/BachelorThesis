#pragma once

#include "ProcessingStep.h"

class BiliteralFilterStep : public ProcessingStep
{
public:
	BiliteralFilterStep(void);
	~BiliteralFilterStep(void);

	void apply( cv::gpu::GpuMat * image );
};

