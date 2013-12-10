#include "ErosionStep.h"


ErosionStep::ErosionStep( QWidget *parent  ) :
	iterations( 1 ),
	point( -1 )
{
	controls = new ErosionStepWidget( this );

	connect( controls, SIGNAL( kernelSizeChanged( int ) ), ( QWidget* )this, SLOT( kernelSizeChanged( int ) ) );
	connect( controls, SIGNAL( iterationChanged( int ) ), ( QWidget* )this, SLOT( iterationChanged( int ) ) );
}


ErosionStep::~ErosionStep(void)
{
	delete controls;
}

void ErosionStep::apply( cv::gpu::GpuMat * image )
{
	if( isActive()  )
	{
		cv::Mat tmp;
		image->download( tmp );
		cv::erode( tmp, tmp, getKernel(), cv::Point( point, point ), iterations, 1, 1 );
		image->upload( tmp );
	}
}

void ErosionStep::kernelSizeChanged( int ksize )
{
	this->setKernelSize( ksize );
}

void ErosionStep::iterationChanged( int _iterations )
{
	this->iterations = _iterations;
}

void ErosionStep::toggleConfigWindow()
{
	controls->setVisible( !controls->isVisible() );
}
