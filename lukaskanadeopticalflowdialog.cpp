#include "lukaskanadeopticalflowdialog.h"

LukasKanadeOpticalFLowDialog::LukasKanadeOpticalFLowDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect( ui.itersSlider, SIGNAL( valueChanged( int ) ), this, SIGNAL( itersValueChanged( int ) ) ); 
}

LukasKanadeOpticalFLowDialog::~LukasKanadeOpticalFLowDialog()
{

}