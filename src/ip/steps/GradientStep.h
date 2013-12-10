#pragma once

#include "ProcessingStep.h"
#include "QObject"
#include "../dialogs/gradientstepdialog.h"

class GradientStep : public ProcessingStep
{
	Q_OBJECT
public:
	GradientStep( QWidget *parent = 0 );
	~GradientStep(void);

	void apply( cv::gpu::GpuMat * image );
	void toggleConfigWindow( void );

public slots:
	void iterationsChanged( int _it );
	void kernelSizeChanged( int _k );

private:
	GradientStepDialog * controls;
	int iterations;
};

