#include "BiliteralFilterStep.h"


BiliteralFilterStep::BiliteralFilterStep( QWidget *parent ) :
	d( 0 ),
	sigmaColor( 171 ),
	sigmaSpace( 3 )
{
	controls = new BiliteralFilterStepDialog( this );

	connect( controls, SIGNAL( dChanged( int ) ), this, SLOT( dChanged( int ) ) );
	connect( controls, SIGNAL( sigmaColorChanged( int ) ), this, SLOT( sigmaColorChanged( int ) ) );
	connect( controls, SIGNAL( sigmaSpaceChanged( int ) ), this, SLOT( sigmaSpaceChanged( int ) ) );
}

BiliteralFilterStep::~BiliteralFilterStep(void)
{
	delete controls;
}

void BiliteralFilterStep::apply( cv::gpu::GpuMat * image )
{
	if( isActive()  )
	{
		cv::gpu::GpuMat temp( image->cols, image->rows, CV_8UC1 );
		cv::gpu::cvtColor( *image, processedImage, CV_BGRA2GRAY );
		cv::gpu::bilateralFilter( processedImage, temp, d, sigmaColor, sigmaSpace );
		cv::gpu::cvtColor( temp, *image, CV_GRAY2BGRA );
	}
}

void BiliteralFilterStep::toggleConfigWindow()
{
	controls->setVisible( !controls->isVisible() );
}

void BiliteralFilterStep::dChanged( int _d )
{
	this->d = _d;
}

void BiliteralFilterStep::sigmaColorChanged( int _sigmaColor )
{
	this->sigmaColor = _sigmaColor;
}

void BiliteralFilterStep::sigmaSpaceChanged( int _sigmaSpace )
{
	this->sigmaSpace = _sigmaSpace;
}
