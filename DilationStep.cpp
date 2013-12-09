#include "DilationStep.h"

DilationStep::DilationStep( QWidget *parent ) :
	//QWidget( parent ),
	point( -1 ),
	iterations( 1 )
{
	controls = new DilationStepWidget( this );

	connect( controls, SIGNAL( kernelSizeChanged( int ) ), ( QWidget* )this, SLOT( kernelSizeChangedD( int ) ) );
	connect( controls, SIGNAL( pointPositionChanged( int ) ), ( QWidget* )this, SLOT( pointChangedD( int ) ) );
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
		cv::Mat tmp;
		image->download( tmp );
		cv::dilate( tmp, tmp, getKernel(), cv::Point( point, point ), iterations, 1, 1 );
		image->upload( tmp );
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

void DilationStep::pointChangedD( int _point )
{
	this->point = _point;
}

void DilationStep::iterationChangedD( int _iterations )
{
	this->iterations = _iterations;
}
