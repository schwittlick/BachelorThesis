#ifndef CLOSESTEPDIALOG_H
#define CLOSESTEPDIALOG_H

#include <QDialog>
#include "ui_CloseStepDialog.h"

class CloseStepDialog : public QDialog
{
	Q_OBJECT

public:
	CloseStepDialog(QWidget *parent = 0);
	~CloseStepDialog();

signals:
	void kernelSizeChanged( int value );
	void iterationChanged( int value );

private:
	Ui::CloseStepDialog ui;
};

#endif // CLOSESTEPDIALOG_H
