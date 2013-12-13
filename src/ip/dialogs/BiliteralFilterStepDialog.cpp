#include "BiliteralFilterStepDialog.h"

BiliteralFilterStepDialog::BiliteralFilterStepDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect( ui.dSlider, SIGNAL( valueChanged( int ) ), this, SIGNAL( dChanged( int ) ) );
	//connect( ui.borderTypeSlider, SIGNAL( valueChanged( int ) ), this, SIGNAL( borderTypeChanged( int ) ) );
	connect( ui.sigmaColorSlider, SIGNAL( valueChanged( int ) ), this, SIGNAL( sigmaColorChanged( int ) ) );
	connect( ui.sigmaSpaceSlider, SIGNAL( valueChanged( int ) ), this, SIGNAL( sigmaSpaceChanged( int ) ) );
}

BiliteralFilterStepDialog::~BiliteralFilterStepDialog()
{

}
