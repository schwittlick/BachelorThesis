#pragma once

#include "ProcessingStep.h"

class OpenStep : public ProcessingStep
{
public:
	OpenStep(void);
	~OpenStep(void);

	void apply( cv::gpu::GpuMat * image );
};

