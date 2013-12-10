#include "CloseStep.h"


CloseStep::CloseStep( QWidget *parent ) :
	iterations( 1 )
{
	controls = new CloseStepDialog( this );

	connect( controls, SIGNAL( kernelSizeChanged( int ) ), this, SLOT( kernelSizeChanged( int ) ) );
	connect( controls, SIGNAL( iterationChanged( int ) ), this, SLOT( iterationChanged( int ) ) );
}


CloseStep::~CloseStep(void)
{
	delete controls;
}

void CloseStep::apply( cv::gpu::GpuMat * image )
{
	if( isActive()  )
	{
		cv::gpu::morphologyEx( *image, *image, cv::MORPH_CLOSE, getKernel(), cv::Point( -1, -1 ), iterations );
	}
}

void CloseStep::toggleConfigWindow()
{
	controls->setVisible( !controls->isVisible() );
}

void CloseStep::kernelSizeChanged( int ksize )
{
	this->setKernelSize( ksize );
}

void CloseStep::iterationChanged( int _iterations )
{
	this->iterations = _iterations;
}