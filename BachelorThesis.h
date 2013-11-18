#ifndef BACHELORTHESIS_H
#define BACHELORTHESIS_H

#include <QtWidgets/QMainWindow>
#include "ui_BachelorThesis.h"

#include "VideoReader.h"

#include "src/misc/Timer.h"

#include "src/opticalflow/LukasKanadeOpticalFlow.h"

#include "src/ip/BackgroundSubtractor.h"
#include "src/ip/Blur.h"
#include "src/ip/Denoiser.h"
#include "src/ip/MeanShifter.h"

#include "lukaskanadeopticalflowdialog.h"

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
	Blur blur;
	MeanShifter meanshifter;

	LukasKanadeOpticalFLowDialog * lukasKanadeOpticalFlowDialog;

	int blurAmount;
	int playbackSpeed;
	bool doBackgroundSubtraction;

public slots:
	void loadImage( void );
	void openFile( void );
	void openSampleFile( void );
	void changePlaybackSpeed( int _playbackSpeed );
	void startVideo( void );
	void jumpToFrame( int _frameNr );
	void toggleBackgroundSubtraction( bool _doBackgroundSubtraction );
	void blurAmountChanged( int _blurAmount );
	void openLukasKanadeWindow( void );

	void changeLKIters( int _iters );
	void changeLKMaxlevel( int _maxLevel );
	void changeLKWinSize( int _winSize );
};

#endif // BACHELORTHESIS_H
