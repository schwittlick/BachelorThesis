#pragma once

#include "ProcessingStep.h"
#include "QObject"
#include "src/ip/dialogs/BlackHatStepDialog.h"

class BlackHatStep : public ProcessingStep
{
	Q_OBJECT
public:
	BlackHatStep( QWidget *parent = 0 );
	~BlackHatStep(void);

	void apply( cv::gpu::GpuMat * image );
	void toggleConfigWindow( void );

public slots:
	void kernelSizeChanged( int ksize );
	void iterationChanged( int iterations );

private:
	BlackHatStepDialog * controls;
	int iterations;
};

