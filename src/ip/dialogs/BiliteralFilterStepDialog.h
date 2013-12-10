#ifndef BILITERALFILTERSTEPDIALOG_H
#define BILITERALFILTERSTEPDIALOG_H

#include <QDialog>
#include "ui_BiliteralFilterStepDialog.h"

class BiliteralFilterStepDialog : public QDialog
{
	Q_OBJECT

public:
	BiliteralFilterStepDialog(QWidget *parent = 0);
	~BiliteralFilterStepDialog();

signals:
	void dChanged( int val );
	void borderTypeChanged( int val );
	void sigmaColorChanged( int val );
	void sigmaSpaceChanged( int val );
private:
	Ui::BiliteralFilterStepDialog ui;
};

#endif // BILITERALFILTERSTEPDIALOG_H
