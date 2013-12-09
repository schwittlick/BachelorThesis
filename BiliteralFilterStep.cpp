#include "BiliteralFilterStep.h"


BiliteralFilterStep::BiliteralFilterStep( QWidget *parent ) :
	d( 0 ),
	sigmaColor( 171 ),
	sigmaSpace( 3 ),
	borderType( 0 )
{
	controls = new BiliteralFilterStepDialog( this );

	connect( controls, SIGNAL( dChanged( int ) ), this, SLOT( dChanged( int ) ) );
	connect( controls, SIGNAL( borderTypeChanged( int ) ), this, SLOT( borderTypeChanged( int ) ) );
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
		cv::Mat im;
		image->download( im );
		cv::cvtColor( im, im, CV_BGRA2GRAY );
		cv::Mat out;
		cv::bilateralFilter( im, out, d, sigmaColor, sigmaSpace, borderType );
		cv::cvtColor( out, out, CV_GRAY2BGRA );
		image->upload( out );
	}
}

void BiliteralFilterStep::toggleConfigWindow()
{
	controls->setVisible( !controls->isVisible() );
}

void BiliteralFilterStep::dChanged( int _d )
{
	std::cout << "d" << std::endl;
	this->d = _d;
}

void BiliteralFilterStep::borderTypeChanged( int _borderType )
{
	std::cout << "border" << std::endl;
	this->borderType = _borderType;
}

void BiliteralFilterStep::sigmaColorChanged( int _sigmaColor )
{
	std::cout << "color" << std::endl;
	this->sigmaColor = _sigmaColor;
}

void BiliteralFilterStep::sigmaSpaceChanged( int _sigmaSpace )
{
	std::cout << "space" << std::endl;
	this->sigmaSpace = _sigmaSpace;
}
