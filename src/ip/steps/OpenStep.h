#pragma once

#include "ProcessingStep.h"

#include "QObject"
#include "../dialogs/OpenStepDialog.h"

class OpenStep : public ProcessingStep
{
	Q_OBJECT
public:
	OpenStep( QWidget *parent = 0 );
	~OpenStep(void);

	void apply( cv::gpu::GpuMat * image );
	void toggleConfigWindow( void );

public slots:
	void iterationsChanged( int _it );
	void kernelSizeChanged( int _k );

private:
	OpenStepDialog * controls;
	int iterations;
};

