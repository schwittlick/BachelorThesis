#include "ThresholdStep.h"


ThresholdStep::ThresholdStep( QWidget *parent ) :
	threshold( 127 ),
	maxval( 255 )
{
	controls = new ThresholdStepDialog( this );

	connect( controls, SIGNAL( thresholdChanged( int ) ), this, SLOT( thresholdChanged( int ) ) );
	connect( controls, SIGNAL( maxValChanged( int ) ), this, SLOT( maxValChanged( int ) ) );
}

ThresholdStep::~ThresholdStep(void)
{
	delete controls;
}

void ThresholdStep::apply( cv::gpu::GpuMat * image )
{
	if( this->isActive() )
	{
		cv::gpu::GpuMat tmpMat;
		cv::gpu::cvtColor( *image, tmpMat, CV_BGRA2GRAY );
		cv::gpu::threshold( tmpMat, tmpMat, this->threshold, this->maxval, 0 );
		cv::gpu::cvtColor( tmpMat, *image, CV_GRAY2BGRA );
	}
}

void ThresholdStep::toggleConfigWindow()
{
	controls->setVisible( !controls->isVisible() );
}

void ThresholdStep::thresholdChanged( int _th )
{
	this->threshold = _th;
}

void ThresholdStep::maxValChanged( int _maxval )
{
	this->maxval = _maxval;
}
