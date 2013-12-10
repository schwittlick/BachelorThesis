#pragma once

#include "ProcessingStep.h"
#include "QObject"
#include "../dialogs/MedianFilterStepDialog.h"

class MedianFilterStep : public ProcessingStep
{
		Q_OBJECT
public:
	MedianFilterStep( QWidget *parent = 0	);
	~MedianFilterStep(void);

	void apply( cv::gpu::GpuMat * image );
	void toggleConfigWindow( void );

public slots:
	void iterationsChanged( int _it );
	void kernelSizeChanged( int _k );

private:
	MedianFilterStepDialog * controls;
	int iterations;
	int kernelSize;
};

