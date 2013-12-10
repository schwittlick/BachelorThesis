#include "MedianFilterStepDialog.h"

MedianFilterStepDialog::MedianFilterStepDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect( ui.iterationsSlider, SIGNAL( valueChanged( int ) ), this, SIGNAL( iterationsChanged( int ) ) );
	connect( ui.kernelSizeSlider, SIGNAL( valueChanged( int ) ), this, SIGNAL( kernelSizeChanged( int ) ) );
}

MedianFilterStepDialog::~MedianFilterStepDialog()
{

}
