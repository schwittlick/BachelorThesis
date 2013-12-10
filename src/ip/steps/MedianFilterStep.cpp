#include "MedianFilterStep.h"


MedianFilterStep::MedianFilterStep(void)
{
}


MedianFilterStep::~MedianFilterStep(void)
{
}

void MedianFilterStep::apply( cv::gpu::GpuMat * image )
{
	if( isActive()  )
	{
		cv::Mat im;
		image->download( im );
		cv::medianBlur( im, im, 11 );
		image->upload( im );
	}
}
