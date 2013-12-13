#include "OpticalFlowSelectorDialog.h"

OpticalFlowSelectorDialog::OpticalFlowSelectorDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect( ui.radioLukasKanade, SIGNAL( clicked( ) ), this, SIGNAL( lukasKanadeActivated() ) );
	connect( ui.radioFarneback, SIGNAL( clicked( ) ), this, SIGNAL( farnebackActivated() ) );
	connect( ui.radioBlockMatching, SIGNAL( clicked( ) ), this, SIGNAL( blockMatchingActivated() ) );
	connect( ui.radioBrox, SIGNAL( clicked( ) ), this, SIGNAL( broxActivated() ) );
	connect( ui.radioDualTVL1, SIGNAL( clicked( ) ), this, SIGNAL( dualTVL1Activated() ) );
	connect( ui.radioHS, SIGNAL( clicked( ) ), this, SIGNAL( hsActivated() ) );

	connect( ui.configLukasKanade, SIGNAL( clicked( ) ), this, SIGNAL( lukasKanadeDialogToggled() ) );
	connect( ui.configFarneback, SIGNAL( clicked( ) ), this, SIGNAL( farnebackDialogToggled() ) );
	connect( ui.configBlockMatching, SIGNAL( clicked( ) ), this, SIGNAL( blockMatchingDialogToggled() ) );
	connect( ui.configBrox, SIGNAL( clicked( ) ), this, SIGNAL( brockDialogToggled() ) );
	connect( ui.configDualTVL1, SIGNAL( clicked( ) ), this, SIGNAL( dualTVL1DialogToggled() ) );
	connect( ui.configHS, SIGNAL( clicked( ) ), this, SIGNAL( hsDialogToggled() ) );
}

OpticalFlowSelectorDialog::~OpticalFlowSelectorDialog()
{

}
