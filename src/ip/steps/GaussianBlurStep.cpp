#include "GaussianBlurStep.h"


GaussianBlurStep::GaussianBlurStep(void)
{
}


GaussianBlurStep::~GaussianBlurStep(void)
{
}

void GaussianBlurStep::apply( cv::gpu::GpuMat * image )
{
	if( isActive()  )
	{
		cv::gpu::GaussianBlur( *image, *image, cv::Size( 13, 13 ), 0 );
	}
}
