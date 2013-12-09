#ifndef BACKGROUNDSUBTRACTIONSTEPDIALOG_H
#define BACKGROUNDSUBTRACTIONSTEPDIALOG_H

#include <QDialog>
#include "ui_BackgroundSubtractionStepDialog.h"

class BackgroundSubtractionStepDialog : public QDialog
{
	Q_OBJECT

public:
	BackgroundSubtractionStepDialog(QWidget *parent = 0);
	~BackgroundSubtractionStepDialog();

signals:
	void typeChanged( int );
	void learningRateChanged( int );
private:
	Ui::BackgroundSubtractionStepDialog ui;
};

#endif // BACKGROUNDSUBTRACTIONSTEPDIALOG_H
