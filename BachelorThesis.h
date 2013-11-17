#ifndef BACHELORTHESIS_H
#define BACHELORTHESIS_H

#include <QtWidgets/QMainWindow>
#include "ui_BachelorThesis.h"

#include "VideoReader.h"
#include "Timer.h"
#include "BackgroundSubtractor.h"
#include "LukasKanadeOpticalFlow.h"

class BachelorThesis : public QMainWindow
{
	Q_OBJECT

public:
	BachelorThesis(QWidget *parent = 0);
	~BachelorThesis();

	static void closeFrameWindow( void );

private:
	Ui::BachelorThesisClass ui;

	VideoReader videoReader;
	Timer timer;
	BackgroundSubtractor bg;
	LukasKanadeOpticalFlow lkflow;


	int playbackSpeed;
	bool doBackgroundSubtraction;

public slots:
	void loadImage( void );
	void openFile( void );
	void changePlaybackSpeed( int _playbackSpeed );
	void startVideo( void );
	void jumpToFrame( int _frameNr );
	void toggleBackgroundSubtraction( bool _doBackgroundSubtraction );
};

#endif // BACHELORTHESIS_H
