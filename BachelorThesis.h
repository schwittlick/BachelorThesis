#ifndef BACHELORTHESIS_H
#define BACHELORTHESIS_H

#include <QtWidgets/QMainWindow>
#include "ui_BachelorThesis.h"

#include "VideoReader.h"
#include "Timer.h"

class BachelorThesis : public QMainWindow
{
	Q_OBJECT

public:
	BachelorThesis(QWidget *parent = 0);
	~BachelorThesis();

private:
	Ui::BachelorThesisClass ui;

	VideoReader videoReader;
	Timer timer;

	int playbackSpeed;

public slots:
	void loadImage( void );
	void openFile( void );
	void changePlaybackSpeed( int _playbackSpeed );
};

#endif // BACHELORTHESIS_H
