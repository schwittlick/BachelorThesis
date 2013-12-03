#include "BiliteralFilterStep.h"


BiliteralFilterStep::BiliteralFilterStep(void)
{
}


BiliteralFilterStep::~BiliteralFilterStep(void)
{
}

void BiliteralFilterStep::apply( cv::gpu::GpuMat * image )
{
	if( isActive()  )
	{
		cv::Mat im;
		image->download( im );
		cv::cvtColor( im, im, CV_BGRA2GRAY );
		cv::Mat out;
		cv::bilateralFilter( im, out, 0, 171, 3, 0 );
		cv::cvtColor( out, out, CV_GRAY2BGRA );
		image->upload( out );
	}
}
