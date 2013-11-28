#include "BachelorThesis.h"
#include "src/misc/SystemInfo.h"

#include <thread>

#include "QTimer"
#include "QFileDialog"
#include "QLabel"
#include "QRectF"
#include "QPainter"

BachelorThesis::BachelorThesis(QWidget *parent)
	: QMainWindow(parent),
	videoReader( VideoReader::Type::GPU ),
	playbackSpeed( 1 ),
	doBackgroundSubtraction( false ),
	doMeanShiftFiltering( false ),
	blurAmount( 1 ),
	isMouseButtonDown( false ),
	isVideoPaused( true )
{

	ui.setupUi(this);

	timer = Timer();	

	lukasKanadeOpticalFlowDialog = new LukasKanadeOpticalFLowDialog( this );
	hardwareInfoDialog = new HardwareInfoDialog( this );
	imageProcessorWidget = new ImageProcessorWidget( this );
	imageProcessorWidget->show();

	// passes all events for the videoLabel to this class and handles them via a eventfilter
	ui.videoLabel->installEventFilter( this );
	origin = QPoint( 0, 0 );
	roiSelector = new QRubberBand(QRubberBand::Rectangle, ui.videoLabel);
	roiSelector->setGeometry(QRect(QPoint( 0, 0 ), QPoint( 720, 576 ) ).normalized());

	cv::gpu::setDevice( 0 );

	connect( ui.actionOpen_File,			SIGNAL( triggered() ),				this,	SLOT( openFile() ) );
	connect( ui.verticalSlider,				SIGNAL( valueChanged( int ) ),		this,	SLOT( changePlaybackSpeed( int ) ) );
	connect( ui.pushButton,					SIGNAL( clicked() ),				this,	SLOT( startVideo() ) );
	// TODO: fix this, it should only call this slot if the slider is moved by hand
	//connect( ui.progressBarSlider,			SIGNAL( valueChanged( int) ),		this,	SLOT( jumpToFrame( int ) ) );
	connect( ui.checkBox,					SIGNAL( toggled( bool ) ),			this,	SLOT( toggleBackgroundSubtraction( bool ) ) );
	connect( ui.checkBox_2,					SIGNAL( toggled( bool ) ),			this,	SLOT( toggleMeanShiftFiltering( bool ) ) );
	connect( ui.blurSlider,					SIGNAL( valueChanged( int ) ),		this,	SLOT( blurAmountChanged( int ) ) );
	connect( ui.actionOpen_Sample,			SIGNAL( triggered() ),				this,	SLOT( openSampleFile() ) );

	connect( ui.actionPyrLukasKanade,		SIGNAL( triggered() ),				this,	SLOT( openLukasKanadeWindow( ) ) );
	connect( ui.actionHardware_Info,		SIGNAL( triggered() ),				this,	SLOT( openHardwareInfoDialog() ) );

	connect( lukasKanadeOpticalFlowDialog,	SIGNAL( itersValueChanged( int ) ), this,	SLOT( changeLKIters( int ) ) );
}

BachelorThesis::~BachelorThesis()
{
	delete hardwareInfoDialog;
	delete lukasKanadeOpticalFlowDialog;
	delete imageProcessorWidget;
	delete roiSelector;
}

void BachelorThesis::loadImage() 
{
	if( videoReader.isOpen() && !isVideoPaused )
	{
		timer.start();
		cv::gpu::GpuMat * originalImage;
		cv::gpu::GpuMat processedImage;

		// loading new frames. the amount of skipped frames is indicated by playbackSpeed
		for( int i = 0; i < playbackSpeed; i++ )
		{
			originalImage = videoReader.getNextImage_GPU();
		}

		// get the selected area
		QPoint maxSize( originalImage->cols, originalImage->rows );
		QRect roi = roiSelector->geometry();

		// adjust the roisize according to the maximum dimensions
		adjustRoiSize( roiSelector->geometry(), roi, maxSize );

		// initializes a new section gpumat with the size of the roi and the imagetype of the incoming image
		cv::gpu::GpuMat section( roi.width(), roi.height(), originalImage->type() );
		// init a cv::Rect with the properties of the ROI
		cv::Rect cvSelectedRect = cv::Rect( roi.x(), roi.y(), roi.width(), roi.height() );
		// a new local copy of the current image
		cv::gpu::GpuMat tempMat = *originalImage;
		// select a part of this new image ( position and size is stored in the passed cv::Rect) and copy this to the new image
		tempMat(cvSelectedRect).copyTo( section );
		// add the cropped image to the processing pipeline
		pipeline.addImage( &section );
		// start the pipeline ( do the processing )
		pipeline.start();
		// get the processed image
		processedImage = pipeline.getFinishedImage();
		// make a local copy of the entire unprocessed original image
		cv::gpu::GpuMat finalImage = *originalImage;
		// copy the processed image into the original image, exactly at the location of the ROI
		processedImage.copyTo( finalImage( cvSelectedRect ) );
		// convert the cv::gpu::GpuMat into a QPixmap
		QPixmap imagePixmap = QPixmap::fromImage( this->mat2QImage( cv::Mat( finalImage ) ) );
		// display the QPixmap onto the label
		ui.videoLabel->setPixmap( imagePixmap );
		ui.videoLabel->setMaximumHeight( finalImage.cols );
		ui.videoLabel->setMaximumWidth( finalImage.rows );
		ui.videoLabel->adjustSize();
		timer.stop();
		timer.store();
		//std::cout << "it took by average:" << timer.getAverageTimeStdString() << "ms." << std::endl;
		std::cout << "lates was: " << timer.getLatestStdString() << "ms." << std::endl;
		QString elapsed;
		elapsed.append( QString( "%1" ).arg( videoReader.getNormalizedProgress() ) );

		ui.label->setText( elapsed );
		ui.progressBarSlider->setValue( videoReader.getCurrentFrameNr() );
	}
	else
	{
		// no new frame. do nothing
	}
}

void BachelorThesis::openFile( void )
{
	QString fileName = QFileDialog::getOpenFileName( this, tr( "Open File" ), "", tr( "MP4 (*.mp4);; AVI (*.avi)" ) );
	videoReader.open( fileName.toStdString() );
	ui.progressBarSlider->setMaximum( videoReader.getMaxFrames() );
}

void BachelorThesis::changePlaybackSpeed( int _playbackSpeed )
{
	this->playbackSpeed = _playbackSpeed;
}

void BachelorThesis::startVideo( void )
{
	QTimer * timer = new QTimer( this );
	connect( timer, SIGNAL( timeout() ), this, SLOT(loadImage() ) );
	timer->start( 30 );

	isVideoPaused = !isVideoPaused;
	if( isVideoPaused )
	{
		ui.pushButton->setText( QString( "Play" ) );
	}
	else
	{
		ui.pushButton->setText( QString( "Pause" ) );
	}

}

void BachelorThesis::jumpToFrame( int _frameNr )
{
	videoReader.jumpToFrame( _frameNr );
}

void BachelorThesis::toggleBackgroundSubtraction( bool _doBackgroundSubtraction )
{
	doBackgroundSubtraction = _doBackgroundSubtraction;
}

void BachelorThesis::blurAmountChanged( int _blurAmount )
{
	std::cout << "BlurAmount changed to " << _blurAmount << std::endl;
	this->blurAmount = _blurAmount;
}

void BachelorThesis::openLukasKanadeWindow( void )
{
	lukasKanadeOpticalFlowDialog->show();
}

void BachelorThesis::changeLKIters( int _iters )
{
	std::cout << "LKOF: iters: " << _iters << std::endl;
	//this->lkflow.setIters( _iters );
}

void BachelorThesis::changeLKWinSize( int _winSize )
{
	std::cout << "LKOF: winSize: " << _winSize << std::endl;
	//this->lkflow.setWinSize( _winSize );
}

void BachelorThesis::changeLKMaxlevel( int _maxLevel )
{
	std::cout << "LKOF: maxLevel: " << _maxLevel << std::endl;
	//this->lkflow.setMaxLevel( _maxLevel );
}

void BachelorThesis::openSampleFile( void )
{
	//frameHandler.createNewOutput( "VIDEO_GPU", 0, cv::WINDOW_OPENGL );
	//imageLabel.show();
	std::string fileName = "G:\\DB\\Dropbox\\BA\\code\\BachelorThesis\\BachelorThesis\\Fri_Oct_11_compilation.mp4";

	videoReader.open( fileName );
	ui.progressBarSlider->setMaximum( videoReader.getMaxFrames() );

}

void BachelorThesis::toggleMeanShiftFiltering( bool _doMeanShiftFiltering )
{
	this->doMeanShiftFiltering = _doMeanShiftFiltering;
}

void BachelorThesis::openHardwareInfoDialog( void )
{
	this->hardwareInfoDialog->show();
}

QImage BachelorThesis::mat2QImage( cv::Mat const& src )
{
	cv::Mat temp; // make the same cv::Mat
	cvtColor(src, temp,CV_BGR2RGB); // cvtColor Makes a copt, that what i need
	QImage dest((uchar*) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
	QImage dest2(dest);
	dest2.detach(); // enforce deep copy
	return dest2;
}

bool BachelorThesis::eventFilter( QObject *watched, QEvent *e )
{
	if( watched == ui.videoLabel )
	{
		QMouseEvent *me = static_cast < QMouseEvent* >( e );
		switch( e->type() )
		{

		case QEvent::MouseButtonPress:
			origin = me->pos();
			roiSelector->setGeometry(QRect(origin, QSize()));
			roiSelector->show();

			isMouseButtonDown = true;
			return true;
		case QEvent::MouseMove:
			if( isMouseButtonDown )
			{
				roiSelector->setGeometry(QRect(origin, me->pos()).normalized());
			}
			return true;
		case QEvent::MouseButtonRelease:
			roiSelector->hide();
			isMouseButtonDown = false;
			return true;
		}
	}
	return QWidget::eventFilter(watched, e);
}

void BachelorThesis::adjustRoiSize( const QRect & srcRoi, QRect & dstRoi, const QPoint & maxSize )
{
	dstRoi = srcRoi;
	if( srcRoi.x() < 0 )
	{
		dstRoi.setLeft( 0 );
	}
	if( srcRoi.y() < 0 )
	{
		dstRoi.setTop( 0 );
	}
	if( srcRoi.right() >= maxSize.x() )
	{
		dstRoi.setRight( maxSize.x() - 2 );
	}

	if( srcRoi.bottom() >= maxSize.y() )
	{
		dstRoi.setBottom( maxSize.y() - 2 );
	}
	if( srcRoi.isEmpty() )
	{
		dstRoi = QRect( 0, 0, maxSize.x(), maxSize.y() );
	}
}
