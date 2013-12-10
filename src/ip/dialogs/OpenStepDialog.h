#ifndef OPENSTEPDIALOG_H
#define OPENSTEPDIALOG_H

#include <QDialog>
#include "ui_OpenStepDialog.h"

class OpenStepDialog : public QDialog
{
	Q_OBJECT

public:
	OpenStepDialog(QWidget *parent = 0);
	~OpenStepDialog();

signals:
	void kernelSizeChanged( int _k );
	void iterationsChanged( int _it );
private:
	Ui::OpenStepDialog ui;
};

#endif // OPENSTEPDIALOG_H
