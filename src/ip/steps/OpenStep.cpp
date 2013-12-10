#include "OpenStep.h"


OpenStep::OpenStep( QWidget *parent ) :
	iterations( 1 )
{
	controls = new OpenStepDialog( this );

	connect( controls, SIGNAL( iterationsChanged( int ) ), this, SLOT( iterationsChanged( int ) ) );
	connect( controls, SIGNAL( kernelSizeChanged( int ) ), this, SLOT( kernelSizeChanged( int ) ) );
}


OpenStep::~OpenStep(void)
{
	delete controls;
}

void OpenStep::apply( cv::gpu::GpuMat * image )
{
	if( isActive()  )
	{
		cv::gpu::morphologyEx( *image, *image, cv::MORPH_OPEN, getKernel(), cv::Point( -1, -1 ), iterations );
	}
}

void OpenStep::toggleConfigWindow( void )
{
	controls->setVisible( !controls->isVisible() );
}

void OpenStep::iterationsChanged( int _it )
{
	this->iterations = _it;
}

void OpenStep::kernelSizeChanged( int _k )
{
	this->setKernelSize( _k );
}
