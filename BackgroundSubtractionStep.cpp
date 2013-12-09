#include "BackgroundSubtractionStep.h"


BackgroundSubtractionStep::BackgroundSubtractionStep( QWidget *parent ) :
	learningRate( 0.05),
	selectedType( BackgroundSubtractor::Type::MOG )
{
	controls = new BackgroundSubtractionStepDialog( this );

	connect( controls, SIGNAL( learningRateChanged( int ) ), this, SLOT( learningRateChanged( int ) ) );
	connect( controls, SIGNAL( typeChanged( int ) ), this, SLOT( typeChanged( int ) ) );
}


BackgroundSubtractionStep::~BackgroundSubtractionStep(void)
{
	delete controls;
}

void BackgroundSubtractionStep::apply( cv::gpu::GpuMat * image )
{
	if( isActive()  )
	{
		bgs.applyBGS( image, selectedType, learningRate );
	}
}

void BackgroundSubtractionStep::toggleConfigWindow( void )
{
	controls->setVisible( !controls->isVisible() );
}

void BackgroundSubtractionStep::typeChanged( int _type )
{
	this->selectedType = static_cast< BackgroundSubtractor::Type > ( _type );
}

void BackgroundSubtractionStep::learningRateChanged( int _learningRate )
{
	this->learningRate = _learningRate / 100.0;
}
