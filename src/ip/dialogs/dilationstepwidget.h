#ifndef DILATIONSTEPWIDGET_H
#define DILATIONSTEPWIDGET_H

#include <QDialog>
#include "ui_dilationstepwidget.h"

class DilationStepWidget : public QDialog
{
	Q_OBJECT

public:
	DilationStepWidget(QWidget *parent = 0);
	~DilationStepWidget();

signals:
	void kernelSizeChanged( int value );
	void iterationChanged( int value );

private:
	Ui::DilationStepWidget ui;
};

#endif // DILATIONSTEPWIDGET_H
