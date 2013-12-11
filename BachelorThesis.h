#ifndef BACHELORTHESIS_H
#define BACHELORTHESIS_H

#include <QtWidgets/QMainWindow>
#include "QMouseEvent"
#include "ui_BachelorThesis.h"

#include "VideoReader.h"

#include "src/misc/Timer.h"

#include "src/opticalflow/LukasKanadeOpticalFlow.h"

#include "ProcessingPipeline.h"

#include "src/opticalflow/dialogs/lukaskanadeopticalflowdialog.h"
#include "src/misc/hardwareinfodialog.h"

#include "opencv2/ocl/ocl.hpp"
#include "opencv2/core/opengl_interop.hpp"

class BachelorThesis : public QMainWindow
{
	Q_OBJECT

public:
	BachelorThesis( QWidget *parent = 0 );
	~BachelorThesis();

	static void closeFrameWindow( void );

private:
	QImage mat2QImage( cv::Mat const& src );

	Ui::BachelorThesisClass ui;

	ProcessingPipeline * pipeline;

	VideoReader videoReader;
	Timer timer;

	HardwareInfoDialog * hardwareInfoDialog;

	int blurAmount;
	int playbackSpeed;

	bool doBackgroundSubtraction;
	bool doMeanShiftFiltering;

	QRubberBand * roiSelector;
	QPoint origin;
	bool isMouseButtonDown;
	bool isVideoPaused;

	void adjustRoiSize( const QRect & srcRoi, QRect & dstRoi, const QPoint & maxSize );
	bool eventFilter(QObject *watched, QEvent *e);

public slots:
	void loadImage( void );
	void openFile( void );
	void openSampleFile( void );
	void changePlaybackSpeed( int _playbackSpeed );
	void startVideo( void );
	void jumpToFrame( int _frameNr );
	void toggleBackgroundSubtraction( bool _doBackgroundSubtraction );
	void toggleMeanShiftFiltering( bool _doMeanShiftFiltering );
	void blurAmountChanged( int _blurAmount );
	void openHardwareInfoDialog( void );

	void changeLKIters( int _iters );
	void changeLKMaxlevel( int _maxLevel );
	void changeLKWinSize( int _winSize );
};

#endif // BACHELORTHESIS_H
