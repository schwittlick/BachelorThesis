#ifndef GRADIENTSTEPDIALOG_H
#define GRADIENTSTEPDIALOG_H

#include <QDialog>
#include "ui_gradientstepdialog.h"

class GradientStepDialog : public QDialog
{
	Q_OBJECT

public:
	GradientStepDialog(QWidget *parent = 0);
	~GradientStepDialog();

signals:
	void kernelSizeChanged( int _k );
	void iterationsChanged( int _it );

private:
	Ui::GradientStepDialog ui;
};

#endif // GRADIENTSTEPDIALOG_H
