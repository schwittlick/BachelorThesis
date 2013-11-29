#include "OpticalFlowFarnebackConfigDialog.h"

OpticalFlowFarnebackConfigDialog::OpticalFlowFarnebackConfigDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect( ui.slider_winSize, SIGNAL( valueChanged( int ) ), parent, SLOT( changedWinSize( int ) ) );
	connect( ui.slider_iterations, SIGNAL( valueChanged( int ) ), parent, SLOT( changedIterations( int ) ) );
	connect( ui.slider_levels, SIGNAL( valueChanged( int ) ), parent, SLOT( changedLevels( int ) ) );
	connect( ui.slider_poly_n, SIGNAL( valueChanged( int ) ), parent, SLOT( changedPolyN( int ) ) );
	connect( ui.slider_poly_sigma, SIGNAL( valueChanged( int ) ), parent, SLOT( changedPolySigma( int ) ) );
	connect( ui.slider_pyr_scale, SIGNAL( valueChanged( int ) ), parent, SLOT( changedPyrScale( int ) ) );
	connect( ui.slider_stepSize, SIGNAL( valueChanged( int ) ), parent, SLOT( changedStepSize( int ) ) );
	connect( ui.slider_scale, SIGNAL( valueChanged( int ) ), parent, SLOT( changedScale( int ) ) );
}

OpticalFlowFarnebackConfigDialog::~OpticalFlowFarnebackConfigDialog()
{

}