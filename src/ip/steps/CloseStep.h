#pragma once

#include "ProcessingStep.h"
#include "QObject"
#include "src/ip/dialogs/CloseStepDialog.h"

class CloseStep : public ProcessingStep
{
	Q_OBJECT
public:
	CloseStep( QWidget *parent = 0 );
	~CloseStep(void);

	void apply( cv::gpu::GpuMat * image );
	void toggleConfigWindow();

public slots:
	void kernelSizeChanged( int ksize );
	void iterationChanged( int iterations );

private:
	CloseStepDialog * controls;
	int iterations;
};

