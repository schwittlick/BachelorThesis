#pragma once

#include "ProcessingStep.h"
#include "QObject"
#include "QWidget"
#include "src/ip/dialogs/ErosionStepWidget.h"

class ErosionStep : public ProcessingStep
{
	Q_OBJECT
public:
	ErosionStep( QWidget *parent = 0 );
	~ErosionStep(void);

	void apply( cv::gpu::GpuMat * image );

	void toggleConfigWindow( void );

public slots:
	void kernelSizeChanged( int ksize );
	void iterationChanged( int iterations );

private:
	ErosionStepWidget * controls;
	int point;
	int iterations;
};

