#include "BackgroundSubtractionStepDialog.h"

BackgroundSubtractionStepDialog::BackgroundSubtractionStepDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect( ui.comboBox, SIGNAL( activated( int ) ), this, SIGNAL( typeChanged( int ) ) );
	connect( ui.slider_learningrate, SIGNAL( valueChanged( int ) ), this, SIGNAL( learningRateChanged( int ) ) );
}

BackgroundSubtractionStepDialog::~BackgroundSubtractionStepDialog()
{

}
