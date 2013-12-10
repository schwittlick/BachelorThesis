#include "TopHatStep.h"


TopHatStep::TopHatStep( QWidget *parent )
{
	controls = new TopHatDialog( this );

	connect( controls, SIGNAL( kernelSizeChanged( int ) ), this, SLOT( kernelSizeChanged( int ) ) );
	connect( controls, SIGNAL( iterationsChanged( int ) ), this, SLOT( iterationsChanged( int ) ) );
}


TopHatStep::~TopHatStep(void)
{
	delete controls;
}

void TopHatStep::apply( cv::gpu::GpuMat * image )
{
	if( isActive()  )
	{
		cv::Mat tmp;
		image->download( tmp );
		cv::morphologyEx( tmp, tmp, CV_MOP_TOPHAT, getKernel(), cv::Point( getKernelSize(), getKernelSize() ), itertations );
		image->upload( tmp );
	}
}

void TopHatStep::toggleConfigWindow()
{
	controls->setVisible( !controls->isVisible() );
}

void TopHatStep::iterationsChanged( int _it )
{
	this->itertations = _it;
}

void TopHatStep::kernelSizeChanged( int _k )
{
	this->setKernelSize( _k );
}
