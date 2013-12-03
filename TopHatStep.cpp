#include "TopHatStep.h"


TopHatStep::TopHatStep(void)
{
}


TopHatStep::~TopHatStep(void)
{
}

void TopHatStep::apply( cv::gpu::GpuMat * image )
{
	if( isActive()  )
	{
		cv::Mat tmp;
		image->download( tmp );
		cv::morphologyEx( tmp, tmp, CV_MOP_TOPHAT, getKernel(), cv::Point( getKernelSize(), getKernelSize() ), 1 );
		image->upload( tmp );
	}
}
