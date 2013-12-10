#include "GaussianBlurStepDialog.h"

GaussianBlurStepDialog::GaussianBlurStepDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect( ui.kernelSizeSlider, SIGNAL( valueChanged( int ) ), this, SIGNAL( kernelSizeChanged( int ) ) );
	connect( ui.sigma1Slider, SIGNAL( valueChanged( int ) ), this, SIGNAL( sigma1Changed( int ) ) );
	connect( ui.sigma2Slider, SIGNAL( valueChanged( int ) ), this, SIGNAL( sigma2Changed( int ) ) );
}

GaussianBlurStepDialog::~GaussianBlurStepDialog()
{

}
