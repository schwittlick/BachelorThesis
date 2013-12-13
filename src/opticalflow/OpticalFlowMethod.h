#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/gpu/gpu.hpp>

#include <iostream>

#include "QObject"
#include "QWidget"

class OpticalFlowMethod : public QWidget
{
	Q_OBJECT
public:
	OpticalFlowMethod( QWidget *parent = 0 );
	~OpticalFlowMethod(void);

	virtual void apply( cv::gpu::GpuMat * image ) = 0;

//public slots:
	virtual void toggleConfigWindow( void ) = 0;
	virtual void activate( void ) = 0;
};

