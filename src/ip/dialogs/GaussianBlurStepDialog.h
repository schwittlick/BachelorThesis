#ifndef GAUSSIANBLURSTEPDIALOG_H
#define GAUSSIANBLURSTEPDIALOG_H

#include <QDialog>
#include "ui_GaussianBlurStepDialog.h"

class GaussianBlurStepDialog : public QDialog
{
	Q_OBJECT

public:
	GaussianBlurStepDialog(QWidget *parent = 0);
	~GaussianBlurStepDialog();

signals:
	void kernelSizeChanged( int _ksize );
	void sigma1Changed( int _sigma1 );
	void sigma2Changed( int _sigma2 );

private:
	Ui::GaussianBlurStepDialog ui;
};

#endif // GAUSSIANBLURSTEPDIALOG_H
