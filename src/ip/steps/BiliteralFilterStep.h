#pragma once

#include "ProcessingStep.h"
#include "QObject"
#include "QWidget"
#include "src/ip/dialogs/BiliteralFilterStepDialog.h"

class BiliteralFilterStep : public ProcessingStep
{
	Q_OBJECT
public:
	BiliteralFilterStep( QWidget *parent = 0 );
	~BiliteralFilterStep(void);

	void apply( cv::gpu::GpuMat * image );
	void toggleConfigWindow();

public slots:
	void dChanged( int _d );
	void borderTypeChanged( int _borderType );
	void sigmaColorChanged( int _sigmaColor );
	void sigmaSpaceChanged( int _sigmaSpace );

private:
	BiliteralFilterStepDialog * controls;
	int d, borderType;
	double sigmaColor, sigmaSpace;
};

