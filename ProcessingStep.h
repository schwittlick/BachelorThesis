#pragma once

#include "opencv2/gpu/gpu.hpp"
#include "opencv2/core/core.hpp"

#include <iostream>

#include "QObject"
#include "QWidget"

class ProcessingStep : public QWidget
{
	Q_OBJECT
public:
	ProcessingStep( QWidget *parent = 0 );
	~ProcessingStep(void);

	virtual void apply( cv::gpu::GpuMat * mat ) = 0;
	void toggle();
	virtual void toggleConfigWindow( void );
	bool isActive( void );
	void setKernelSize( int _kernelSize );
	cv::Mat getKernel( void );
	int getKernelSize( void );

private:
	bool activated;
	int kernelSize;
	cv::Mat kernel;
};

