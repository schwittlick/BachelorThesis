#pragma once

#include "ProcessingStep.h"
#include "src/ip/BackgroundSubtractor.h"
#include "BackgroundSubtractionStepDialog.h"

class BackgroundSubtractionStep : public ProcessingStep
{
	Q_OBJECT
public:
	BackgroundSubtractionStep( QWidget *parent = 0 );
	~BackgroundSubtractionStep(void);

	void apply( cv::gpu::GpuMat * image );
	void toggleConfigWindow( void );

public slots:
	void typeChanged( int _type );
	void learningRateChanged( int _learningRate );
private:
	BackgroundSubtractor bgs;
	BackgroundSubtractionStepDialog * controls;
	double learningRate;
	BackgroundSubtractor::Type selectedType;
};

