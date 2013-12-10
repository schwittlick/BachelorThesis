#include "CloseStepDialog.h"

CloseStepDialog::CloseStepDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect( ui.iterationsSlider, SIGNAL( valueChanged( int ) ), this, SIGNAL( iterationChanged( int ) ) );
	connect( ui.kernelSizeSlider, SIGNAL( valueChanged( int ) ), this, SIGNAL( kernelSizeChanged( int ) ) );
}

CloseStepDialog::~CloseStepDialog()
{

}
