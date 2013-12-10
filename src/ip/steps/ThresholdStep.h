#pragma once

#include "src/ip/steps/ProcessingStep.h"
#include "ThresholdStepDialog.h"
#include "QObject"

class ThresholdStep : public ProcessingStep
{
	Q_OBJECT
public:
	ThresholdStep( QWidget *parent = 0 );
	~ThresholdStep(void);

	void apply( cv::gpu::GpuMat * image );
	void toggleConfigWindow();

public slots:
	void thresholdChanged( int _th );
	void maxValChanged( int _maxval );

private:
	ThresholdStepDialog * controls;
	int threshold;
	int maxval;
};

