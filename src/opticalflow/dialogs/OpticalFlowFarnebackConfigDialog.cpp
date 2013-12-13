#include "OpticalFlowFarnebackConfigDialog.h"

OpticalFlowFarnebackConfigDialog::OpticalFlowFarnebackConfigDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect( ui.slider_winSize, SIGNAL( valueChanged( int ) ), this, SIGNAL( changedWinSize( int ) ) );
	connect( ui.slider_iterations, SIGNAL( valueChanged( int ) ), this, SIGNAL( changedIterations( int ) ) );
	connect( ui.slider_levels, SIGNAL( valueChanged( int ) ), this, SIGNAL( changedLevels( int ) ) );
	connect( ui.slider_poly_n, SIGNAL( valueChanged( int ) ), this, SIGNAL( changedPolyN( int ) ) );
	connect( ui.slider_poly_sigma, SIGNAL( valueChanged( int ) ), this, SIGNAL( changedPolySigma( int ) ) );
	connect( ui.slider_pyr_scale, SIGNAL( valueChanged( int ) ), this, SIGNAL( changedPyrScale( int ) ) );
	connect( ui.slider_stepSize, SIGNAL( valueChanged( int ) ), this, SIGNAL( changedStepSize( int ) ) );
	connect( ui.slider_scale, SIGNAL( valueChanged( int ) ), this, SIGNAL( changedScale( int ) ) );
	connect( ui.slider_minLength, SIGNAL( valueChanged( int ) ), this, SIGNAL( changedMinLength( int ) ) );
	connect( ui.slider_maxLength, SIGNAL( valueChanged( int ) ), this, SIGNAL( changedMaxLength( int ) ) );
}

OpticalFlowFarnebackConfigDialog::~OpticalFlowFarnebackConfigDialog()
{

}