#include "BackgroundSubtractionStep.h"


BackgroundSubtractionStep::BackgroundSubtractionStep(void)
{
}


BackgroundSubtractionStep::~BackgroundSubtractionStep(void)
{
}

void BackgroundSubtractionStep::apply( cv::gpu::GpuMat * image )
{
	if( isActive()  )
	{
		bgs.applyBGS( image, BackgroundSubtractor::Type::MOG );
	}
}