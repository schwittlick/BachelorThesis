#ifndef THRESHOLDSTEPDIALOG_H
#define THRESHOLDSTEPDIALOG_H

#include <QDialog>
#include "ui_ThresholdStepDialog.h"

class ThresholdStepDialog : public QDialog
{
	Q_OBJECT

public:
	ThresholdStepDialog(QWidget *parent = 0);
	~ThresholdStepDialog();

signals:
	void maxValChanged( int _maxVal );
	void thresholdChanged( int _th );

private:
	Ui::ThresholdStepDialog ui;
};

#endif // THRESHOLDSTEPDIALOG_H
