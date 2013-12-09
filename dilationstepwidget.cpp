#include "dilationstepwidget.h"

DilationStepWidget::DilationStepWidget(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect( ui.horizontalSlider,	SIGNAL( valueChanged( int ) ), this, SIGNAL( kernelSizeChanged( int ) ) );
	connect( ui.horizontalSlider_2, SIGNAL( valueChanged( int ) ), this, SIGNAL( pointPositionChanged( int ) ) );
	connect( ui.horizontalSlider_3, SIGNAL( valueChanged( int ) ), this, SIGNAL( iterationChanged( int ) ) );
}

DilationStepWidget::~DilationStepWidget()
{

}
