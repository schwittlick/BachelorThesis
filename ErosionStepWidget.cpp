#include "ErosionStepWidget.h"

ErosionStepWidget::ErosionStepWidget(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect( ui.horizontalSlider,	SIGNAL( valueChanged( int ) ), this, SIGNAL( kernelSizeChanged( int ) ) );
	connect( ui.horizontalSlider_2, SIGNAL( valueChanged( int ) ), this, SIGNAL( iterationChanged( int ) ) );
}

ErosionStepWidget::~ErosionStepWidget()
{

}
