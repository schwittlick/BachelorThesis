#include "BlackHatStep.h"


BlackHatStep::BlackHatStep( QWidget *parent ) :
	iterations( 1 )
{
	controls = new BlackHatStepDialog( this );

	connect( controls, SIGNAL( kernelSizeChanged( int ) ), this, SLOT( kernelSizeChanged( int ) ) );
	connect( controls, SIGNAL( iterationsChanged( int ) ), this, SLOT( iterationChanged( int ) ) );
}


BlackHatStep::~BlackHatStep(void)
{
	delete controls;
}

void BlackHatStep::apply( cv::gpu::GpuMat * image )
{
	if( isActive() )
	{
		cv::Mat tmp;
		image->download( tmp );
		cv::morphologyEx( tmp, tmp, CV_MOP_BLACKHAT, getKernel(), cv::Point( getKernelSize(), getKernelSize() ), iterations);
		image->upload( tmp );
		//cv::gpu::morphologyEx( *image, *image, cv::MORPH_BLACKHAT, kernel, cv::Point( -1, -1 ), 1 );
	}
}

void BlackHatStep::kernelSizeChanged( int ksize )
{
	this->setKernelSize( ksize );
}

void BlackHatStep::iterationChanged( int _iterations )
{
	this->iterations = _iterations;
}

void BlackHatStep::toggleConfigWindow()
{
	controls->setVisible( !controls->isVisible() );
}
