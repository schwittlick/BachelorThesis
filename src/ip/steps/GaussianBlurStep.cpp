#include "GaussianBlurStep.h"


GaussianBlurStep::GaussianBlurStep( QWidget *parent ) :
	kernelSize( 1 ),
	sigma1( 0.0 ),
	sigma2( 0.0 )
{
	controls = new GaussianBlurStepDialog( this );

	connect( controls, SIGNAL( kernelSizeChanged( int ) ), this, SLOT( kernelSizeChanged( int ) ) );
	connect( controls, SIGNAL( sigma1Changed( int ) ), this, SLOT( sigma1Changed( int ) ) );
	connect( controls, SIGNAL( sigma2Changed( int ) ), this, SLOT( sigma2Changed( int ) ) );
}


GaussianBlurStep::~GaussianBlurStep(void)
{
	delete controls;
}

void GaussianBlurStep::apply( cv::gpu::GpuMat * image )
{
	if( isActive()  )
	{
		cv::gpu::GaussianBlur( *image, *image, cv::Size( kernelSize, kernelSize ), sigma1, sigma2 );
	}
}

void GaussianBlurStep::toggleConfigWindow( void )
{
	controls->setVisible( !controls->isVisible() );
}

void GaussianBlurStep::kernelSizeChanged( int _ksize )
{
	this->kernelSize = _ksize;
	if( this->kernelSize % 2 == 0 )
	{
		this->kernelSize++;
	}
}

void GaussianBlurStep::sigma1Changed( int _sigma1 )
{
	this->sigma1 = _sigma1;
}

void GaussianBlurStep::sigma2Changed( int _sigma2 )
{
	this->sigma2 = _sigma2;
}
