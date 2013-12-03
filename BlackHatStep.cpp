#include "BlackHatStep.h"


BlackHatStep::BlackHatStep(void)
{
}


BlackHatStep::~BlackHatStep(void)
{
}

void BlackHatStep::apply( cv::gpu::GpuMat * image )
{
	if( isActive() )
	{
		cv::Mat tmp;
		image->download( tmp );
		cv::morphologyEx( tmp, tmp, CV_MOP_BLACKHAT, getKernel(), cv::Point( getKernelSize(), getKernelSize() ), 1 );
		image->upload( tmp );
		//cv::gpu::morphologyEx( *image, *image, cv::MORPH_BLACKHAT, kernel, cv::Point( -1, -1 ), 1 );
	}
}
