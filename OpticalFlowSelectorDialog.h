#ifndef OPTICALFLOWSELECTORDIALOG_H
#define OPTICALFLOWSELECTORDIALOG_H

#include <QDialog>
#include "ui_OpticalFlowSelectorDialog.h"

class OpticalFlowSelectorDialog : public QDialog
{
	Q_OBJECT

public:
	OpticalFlowSelectorDialog(QWidget *parent = 0);
	~OpticalFlowSelectorDialog();

signals:
	void lukasKanadeActivated( void );
	void farnebackActivated( void );
	void blockMatchingActivated( void );
	void broxActivated( void );
	void dualTVL1Activated( void );
	void hsActivated( void );

	void lukasKanadeDialogToggled( void );
	void farnebackDialogToggled( void );
	void blockMatchingDialogToggled( void );
	void brockDialogToggled( void );
	void dualTVL1DialogToggled( void );
	void hsDialogToggled( void );

private:
	Ui::OpticalFlowSelectorDialog ui;
};

#endif // OPTICALFLOWSELECTORDIALOG_H
