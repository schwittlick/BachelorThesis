#pragma once

#include "opencv2/gpu/gpu.hpp"
#include "opencv2/core/core.hpp"

#include <iostream>

class ProcessingStep
{
public:
	ProcessingStep(void);
	~ProcessingStep(void);

	virtual void apply( cv::gpu::GpuMat * mat ) = 0;
	void toggle();
	bool isActive( void );
	void setKernelSize( int _kernelSize );
	cv::Mat getKernel( void );
	int getKernelSize( void );

private:
	bool activated;
	int kernelSize;
	cv::Mat kernel;
};

