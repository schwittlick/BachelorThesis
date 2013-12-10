#pragma once

#include "ProcessingStep.h"
#include "QObject"
#include "../dialogs/GaussianBlurStepDialog.h"

class GaussianBlurStep : public ProcessingStep
{
	Q_OBJECT
public:
	GaussianBlurStep( QWidget *parent = 0 );
	~GaussianBlurStep(void);

	void apply( cv::gpu::GpuMat * image );
	void toggleConfigWindow( void );

public slots:
	void kernelSizeChanged( int _ksize );
	void sigma1Changed( int _sigma1 );
	void sigma2Changed( int _sigma2 );

private:
	GaussianBlurStepDialog * controls;
	int kernelSize;
	double sigma1, sigma2;
};

