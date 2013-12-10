#include "ThresholdStepDialog.h"

ThresholdStepDialog::ThresholdStepDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect( ui.thresholdSlider, SIGNAL( valueChanged( int ) ), this, SIGNAL( thresholdChanged( int ) ) );
	connect( ui.maxValSlider, SIGNAL( valueChanged( in ) ), this, SIGNAL( maxValChanged( int ) ) );
}

ThresholdStepDialog::~ThresholdStepDialog()
{

}
