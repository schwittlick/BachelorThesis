#pragma once

#include "ProcessingStep.h"

class CloseStep : public ProcessingStep
{
public:
	CloseStep(void);
	~CloseStep(void);

	void apply( cv::gpu::GpuMat * image );
};

