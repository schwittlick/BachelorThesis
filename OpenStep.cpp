#include "OpenStep.h"


OpenStep::OpenStep(void)
{
}


OpenStep::~OpenStep(void)
{
}

void OpenStep::apply( cv::gpu::GpuMat * image )
{
	if( isActive()  )
	{
		cv::gpu::morphologyEx( *image, *image, cv::MORPH_OPEN, getKernel(), cv::Point( -1, -1 ), 1 );
	}
}
