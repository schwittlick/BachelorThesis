#include "DilationStep.h"

DilationStep::DilationStep( QWidget *parent ) :
	iterations( 1 )
{
	controls = new DilationStepWidget( this );

	connect( controls, SIGNAL( kernelSizeChanged( int ) ), ( QWidget* )this, SLOT( kernelSizeChangedD( int ) ) );
	connect( controls, SIGNAL( iterationChanged( int ) ), ( QWidget* )this, SLOT( iterationChangedD( int ) ) );
}

DilationStep::~DilationStep(void)
{
	delete controls;
}

void DilationStep::apply( cv::gpu::GpuMat * image )
{
	if( isActive() )
	{
		cv::gpu::dilate( *image, processedImage, getKernel(), cv::Point( -1, -1 ), iterations );
		processedImage.copyTo( *image );
	}
}

void DilationStep::toggleConfigWindow()
{
	controls->setVisible( !controls->isVisible() );
}

void DilationStep::kernelSizeChangedD( int ksize )
{
	setKernelSize( ksize );
}

void DilationStep::iterationChangedD( int _iterations )
{
	this->iterations = _iterations;
}
