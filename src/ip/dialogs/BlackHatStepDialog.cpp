#include "BlackHatStepDialog.h"

BlackHatStepDialog::BlackHatStepDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect( ui.kernelSizeSlider, SIGNAL( valueChanged( int ) ), this, SIGNAL( kernelSizeChanged( int ) ) );
	connect( ui.iterationsSlider, SIGNAL( valueChanged( int ) ), this, SIGNAL( iterationsChanged( int ) ) );
}

BlackHatStepDialog::~BlackHatStepDialog()
{

}
