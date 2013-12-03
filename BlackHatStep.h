#pragma once

#include "ProcessingStep.h"

class BlackHatStep : public ProcessingStep
{
public:
	BlackHatStep(void);
	~BlackHatStep(void);

	void apply( cv::gpu::GpuMat * image );
};

