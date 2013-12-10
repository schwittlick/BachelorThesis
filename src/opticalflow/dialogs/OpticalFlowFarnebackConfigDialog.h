#ifndef OPTICALFLOWFARNEBACKCONFIGDIALOG_H
#define OPTICALFLOWFARNEBACKCONFIGDIALOG_H

#include <QDialog>
#include "ui_OpticalFlowFarnebackConfigDialog.h"

class OpticalFlowFarnebackConfigDialog : public QDialog
{
	Q_OBJECT

public:
	OpticalFlowFarnebackConfigDialog(QWidget *parent = 0);
	~OpticalFlowFarnebackConfigDialog();


private:
	Ui::OpticalFlowFarnebackConfigDialog ui;
};

#endif // OPTICALFLOWFARNEBACKCONFIGDIALOG_H
