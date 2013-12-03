#include "DilationStep.h"


DilationStep::DilationStep(void)
{
}


DilationStep::~DilationStep(void)
{
}

void DilationStep::apply( cv::gpu::GpuMat * image )
{
	if( isActive()  )
	{
		cv::Mat tmp;
		image->download( tmp );
		cv::dilate( tmp, tmp, getKernel(), cv::Point( -1, -1 ), 1, 1, 1 );
		image->upload( tmp );
	}
}
