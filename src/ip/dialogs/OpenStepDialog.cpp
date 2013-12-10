#include "OpenStepDialog.h"

OpenStepDialog::OpenStepDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect( ui.iterationsSlider, SIGNAL( valueChanged( int ) ), this, SIGNAL( iterationsChanged( int ) ) );
	connect( ui.kernelSizeSlider, SIGNAL( valueChanged( int ) ), this, SIGNAL( kernelSizeChanged( int ) ) );
}

OpenStepDialog::~OpenStepDialog()
{

}
