#pragma once

#include "ProcessingStep.h"
#include "src/ip/BackgroundSubtractor.h"

class BackgroundSubtractionStep : public ProcessingStep
{
public:
	BackgroundSubtractionStep(void);
	~BackgroundSubtractionStep(void);

	void apply( cv::gpu::GpuMat * image );

private:
	BackgroundSubtractor bgs;
};

