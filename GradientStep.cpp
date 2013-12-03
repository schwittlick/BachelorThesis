#include "GradientStep.h"


GradientStep::GradientStep(void)
{
}


GradientStep::~GradientStep(void)
{
}

void GradientStep::apply( cv::gpu::GpuMat * image )
{
	if( isActive()  )
	{
		cv::Mat tmp;
		image->download( tmp );
		cv::morphologyEx( tmp, tmp, CV_MOP_GRADIENT, getKernel(), cv::Point( getKernelSize(), getKernelSize() ), 1 );
		image->upload( tmp );
		//cv::gpu::morphologyEx( *image, *image, cv::MORPH_GRADIENT, kernel, cv::Point( -1, -1 ), 1 );
	}
}
