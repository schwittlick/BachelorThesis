#ifndef BLACKHATSTEPDIALOG_H
#define BLACKHATSTEPDIALOG_H

#include <QDialog>
#include "ui_BlackHatStepDialog.h"

class BlackHatStepDialog : public QDialog
{
	Q_OBJECT

public:
	BlackHatStepDialog(QWidget *parent = 0);
	~BlackHatStepDialog();

signals:
	void kernelSizeChanged( int _ksize );
	void iterationsChanged( int _it );

private:
	Ui::BlackHatStepDialog ui;
};

#endif // BLACKHATSTEPDIALOG_H
