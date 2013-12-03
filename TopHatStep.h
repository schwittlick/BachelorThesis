#pragma once

#include "ProcessingStep.h"
#include "opencv2/core/core.hpp"
#include "opencv2/gpu/gpu.hpp"

class TopHatStep : public ProcessingStep
{
public:
	TopHatStep(void);
	~TopHatStep(void);

	void apply( cv::gpu::GpuMat * image );
};

