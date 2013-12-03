#include "ErosionStep.h"


ErosionStep::ErosionStep(void)
{
}


ErosionStep::~ErosionStep(void)
{
}

void ErosionStep::apply( cv::gpu::GpuMat * image )
{
	if( isActive()  )
	{
		cv::Mat tmp;
		image->download( tmp );
		cv::erode( tmp, tmp, getKernel(), cv::Point( -1, -1 ), 1, 1, 1 );
		image->upload( tmp );
	}
}
