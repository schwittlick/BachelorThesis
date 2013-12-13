#include "GradientStep.h"


GradientStep::GradientStep( QWidget *parent ) :
	iterations( 1 )
{
	controls = new GradientStepDialog( this );

	connect( controls, SIGNAL( kernelSizeChanged( int ) ), this, SLOT( kernelSizeChanged( int ) ) );
	connect( controls, SIGNAL( iterationsChanged( int ) ), this, SLOT( iterationsChanged( int ) ) );
}


GradientStep::~GradientStep(void)
{
	delete controls;
}

void GradientStep::apply( cv::gpu::GpuMat * image )
{
	if( isActive()  )
	{
		cv::gpu::morphologyEx( *image, processedImage, cv::MORPH_GRADIENT, getKernel(), cv::Point( -1, -1 ), iterations );
		processedImage.copyTo( *image );
	}
}

void GradientStep::toggleConfigWindow( void )
{
	controls->setVisible( !controls->isVisible() );
}

void GradientStep::iterationsChanged( int _it )
{
	this->iterations = _it;
}

void GradientStep::kernelSizeChanged( int _k )
{
	this->setKernelSize( _k );
}
