#include "CloseStep.h"


CloseStep::CloseStep(void)
{
}


CloseStep::~CloseStep(void)
{
}

void CloseStep::apply( cv::gpu::GpuMat * image )
{
	if( isActive()  )
	{
		cv::gpu::morphologyEx( *image, *image, cv::MORPH_CLOSE, getKernel(), cv::Point( -1, -1 ), 1 );
	}
}
