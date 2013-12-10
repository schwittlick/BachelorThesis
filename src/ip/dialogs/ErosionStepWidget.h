#ifndef EROSIONSTEPWIDGET_H
#define EROSIONSTEPWIDGET_H

#include <QDialog>
#include "ui_ErosionStepWidget.h"

class ErosionStepWidget : public QDialog
{
	Q_OBJECT

public:
	ErosionStepWidget(QWidget *parent = 0);
	~ErosionStepWidget();

signals:
	void kernelSizeChanged( int value );
	void iterationChanged( int value );

private:
	Ui::ErosionStepWidget ui;
};

#endif // EROSIONSTEPWIDGET_H
