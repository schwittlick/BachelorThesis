#ifndef MEDIANFILTERSTEPDIALOG_H
#define MEDIANFILTERSTEPDIALOG_H

#include <QDialog>
#include "ui_MedianFilterStepDialog.h"

class MedianFilterStepDialog : public QDialog
{
	Q_OBJECT

public:
	MedianFilterStepDialog(QWidget *parent = 0);
	~MedianFilterStepDialog();

signals:
	void kernelSizeChanged( int _k );
	void iterationsChanged( int _i );

private:
	Ui::MedianFilterStepDialog ui;
};

#endif // MEDIANFILTERSTEPDIALOG_H
