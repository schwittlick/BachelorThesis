#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/gpu/gpu.hpp>

#include <iostream>

#include "QObject"
#include "QWidget"

class OpticalFlow : public QWidget
{
	Q_OBJECT
public:
	OpticalFlow( QWidget *parent = 0 );
	~OpticalFlow(void);

	virtual void apply( cv::gpu::GpuMat * image ) = 0;

//public slots:
	virtual void toggleConfigWindow( void ) = 0;
	virtual void activate( void ) = 0;
};

