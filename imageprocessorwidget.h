#ifndef IMAGEPROCESSORWIDGET_H
#define IMAGEPROCESSORWIDGET_H

#include <QDialog>
#include "QSignalMapper"
#include "QCheckBox"
#include "ui_imageprocessorwidget.h"
#include <iostream>

class ImageProcessorWidget : public QDialog
{
	Q_OBJECT

public:
	ImageProcessorWidget(QWidget *parent = 0);
	~ImageProcessorWidget();

private:
	Ui::ImageProcessorWidget ui;
	QSignalMapper * signalMapper;
	QCheckBox * getCheckBoxByID( int id );
	bool getCheckBoxStatusByID( int id );

public slots:
	void checkBoxClickedByID( int id );

signals:
	void checkBoxClicked( int id );
};

#endif // IMAGEPROCESSORWIDGET_H
