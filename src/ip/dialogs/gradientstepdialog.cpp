#include "gradientstepdialog.h"

GradientStepDialog::GradientStepDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect( ui.kernelSizeSlider, SIGNAL( valueChanged( int ) ), this, SIGNAL( kernelSizeChanged( int ) ) );
	connect( ui.iterationsSlider, SIGNAL( valueChanged( int ) ), this, SIGNAL( iterationsChanged( int ) ) );
}

GradientStepDialog::~GradientStepDialog()
{

}
