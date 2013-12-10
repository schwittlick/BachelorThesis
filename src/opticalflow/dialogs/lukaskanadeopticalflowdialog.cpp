#include "lukaskanadeopticalflowdialog.h"

LukasKanadeOpticalFLowDialog::LukasKanadeOpticalFLowDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect( ui.itersSlider, SIGNAL( valueChanged( int ) ), this, SIGNAL( itersValueChanged( int ) ) ); 
	connect( ui.maxLevelSlider, SIGNAL( valueChanged( int ) ), this, SIGNAL( maxLevelValueChanged( int ) ) ); 

}

LukasKanadeOpticalFLowDialog::~LukasKanadeOpticalFLowDialog()
{

}