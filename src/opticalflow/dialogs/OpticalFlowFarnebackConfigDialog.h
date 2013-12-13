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

signals:
	void changedWinSize( int _winsize );
	void changedIterations( int _it );
	void changedLevels( int _lev );
	void changedPolyN( int _polyn );
	void changedPolySigma( int _polysigma );
	void changedPyrScale( int _pyrscale );
	void changedStepSize( int _stepsize );
	void changedScale( int _scale );
	void changedMinLength( int _minLength );
	void changedMaxLength( int _maxLength );
private:
	Ui::OpticalFlowFarnebackConfigDialog ui;
};

#endif // OPTICALFLOWFARNEBACKCONFIGDIALOG_H
