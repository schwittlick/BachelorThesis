#pragma once

#include "ProcessingStep.h"
#include "opencv2/core/core.hpp"
#include "opencv2/gpu/gpu.hpp"
#include "src/ip/dialogs/TopHatDialog.h"
#include "QObject"

class TopHatStep : public ProcessingStep
{
	Q_OBJECT
public:
	TopHatStep( QWidget *parent = 0 );
	~TopHatStep(void);

	void apply( cv::gpu::GpuMat * image );
	void toggleConfigWindow();

public slots:
	void iterationsChanged( int _it );
	void kernelSizeChanged( int _k );

private:
	TopHatDialog * controls;
	int itertations;
};

