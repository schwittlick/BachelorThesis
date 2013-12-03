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

	QCheckBox * getCheckBoxByID( int id );
	bool getCheckBoxStatusByID( int id );
	QPushButton * getDownButtonById( int id );
	QPushButton * getUpButtonByID( int id );
	QPushButton * getConfigButtonByID( int id );
	QLabel * getLabelByID( int id );

private:
	Ui::ImageProcessorWidget ui;
	QSignalMapper * toggleSignalMapper;
	void setupToggleSignals();
	void setupDownSignals();
	void setupUpSignals();
	void setupConfigSignals();

	QSignalMapper * downSignalMapper;
	QSignalMapper * upSignalMapper;
	QSignalMapper * configSignalMapper;

	

public slots:
	void checkBoxClickedByID( int id );
	void upButtonClickedByID( int id );
	void downButtonClickedByID( int );
	void configButtonCLickedByID( int );

signals:
	void checkBoxClicked( int id );
	void upButtonClicked( int id );
	void downButtonClicked( int id );
	void configButtonClicked( int id );
};

#endif // IMAGEPROCESSORWIDGET_H
