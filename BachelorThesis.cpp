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
	videoReader( VideoReader::Type::CPU ),
	playbackSpeed( 1 ),
	doBackgroundSubtraction( false ),
	doMeanShiftFiltering( false ),
	blurAmount( 1 ),
	isMouseButtonDown( false ),
	isVideoPaused( true ),
	originalImage( 640, 480, CV_8UC4 )
{

	ui.setupUi(this);

	timer = Timer();	

	pipeline = new ProcessingPipeline( );

	hardwareInfoDialog = new HardwareInfoDialog( this );

	// passes all events for the videoLabel to this class and handles them via a eventfilter
	ui.videoLabel->installEventFilter( this );
	ui.originalVideoLabel->installEventFilter( this );
	origin = QPoint( 0, 0 );
	roiSelector = new QRubberBand(QRubberBand::Rectangle, ui.videoLabel);
	roiSelector->setGeometry(QRect(QPoint( 0, 0 ), QPoint( 720, 576 ) ).normalized());

	connect( ui.actionOpen_File,			SIGNAL( triggered() ),				this,		SLOT( openFile() ) );
	connect( ui.pushButton,					SIGNAL( clicked() ),				this,		SLOT( startVideo() ) );
	// TODO: fix this, it should only call this slot if the slider is moved by hand
	//connect( ui.progressBarSlider,			SIGNAL( valueChanged( int) ),		this,	SLOT( jumpToFrame( int ) ) );
	connect( ui.actionOpen_Sample,			SIGNAL( triggered() ),				this,		SLOT( openSampleFile() ) );

	connect( ui.actionHardware_Info,		SIGNAL( triggered() ),				this,		SLOT( openHardwareInfoDialog() ) );

	connect( ui.actionProcesingPipeline,	SIGNAL( triggered() ),				( QObject* ) pipeline,	SLOT( toggleProcessingPipelineConfigWidgetDisplay() ) );
	connect( ui.actionOpticalFlowSelector,	SIGNAL( triggered() ),				( QObject* ) pipeline,	SLOT( toggleOpticalFlowSelectorDialog() ) );
	connect( ui.actionOpen_Video_Stream,	SIGNAL( triggered() ),				this,		SLOT( openVideoStream() ) );


}

BachelorThesis::~BachelorThesis()
{
	delete hardwareInfoDialog;
	delete roiSelector;
	delete pipeline;
}

void BachelorThesis::loadImage() 
{
	if( videoReader.isOpen() && !isVideoPaused )
	{
		timer.start();
		
		cv::gpu::GpuMat processedImage;
		cv::Mat unProcessedImage;

		// loading new frames. the amount of skipped frames is indicated by playbackSpeed
		for( int i = 0; i < playbackSpeed; i++ )
		{
			if( videoReader.selectedType == VideoReader::Type::CPU || videoReader.selectedType == VideoReader::Type::LIVE )
			{
				cv::Mat  temp = videoReader.getNextImage();
				
				cv::cvtColor( temp, temp, CV_BGR2RGBA );
				unProcessedImage = temp;
				if( originalImage.cols != temp.cols || originalImage.rows != temp.rows )
				{
					originalImage = cv::gpu::GpuMat( 640, 480, CV_8UC4 );
				}

				originalImage.upload( temp );
			} else if ( videoReader.selectedType == VideoReader::Type::GPU )
			{
				originalImage = videoReader.getNextImage_GPU();
			}
			
		}

		// get the selected area
		QPoint maxSize( originalImage.cols, originalImage.rows );
		QRect roi = roiSelector->geometry();

		// adjust the roisize according to the maximum dimensions
		adjustRoiSize( roiSelector->geometry(), roi, maxSize );

		// initializes a new section gpumat with the size of the roi and the imagetype of the incoming image
		cv::gpu::GpuMat section( roi.width(), roi.height(), originalImage.type() );
		// init a cv::Rect with the properties of the ROI
		cv::Rect cvSelectedRect = cv::Rect( roi.x(), roi.y(), roi.width(), roi.height() );
		// a new local copy of the current image

		cv::gpu::GpuMat tempMat(originalImage );
		// select a part of this new image ( position and size is stored in the passed cv::Rect) and copy this to the new image
		tempMat(cvSelectedRect).copyTo( section );
		// add the cropped image to the processing pipeline
		pipeline->addImage( &section );
		// start the pipeline ( do the processing )
		pipeline->start();
		// get the processed image
		processedImage = pipeline->getFinishedImage();
		// make a local copy of the entire unprocessed original image
		cv::gpu::GpuMat finalImage( originalImage );
		// copy the processed image into the original image, exactly at the location of the ROI
		processedImage.copyTo( finalImage( cvSelectedRect ) );
		// convert the cv::gpu::GpuMat into a QPixmap
		
		QPixmap imagePixmap = QPixmap::fromImage( this->mat2QImage( cv::Mat( finalImage ) ) );
		// display the QPixmap onto the label
		ui.videoLabel->setPixmap( imagePixmap );
		ui.videoLabel->setMaximumHeight( imagePixmap.width() );
		ui.videoLabel->setMaximumWidth( imagePixmap.height() );
		ui.videoLabel->adjustSize();

		QPixmap originalImagePixmap = QPixmap::fromImage( this->mat2QImage( cv::Mat( unProcessedImage ) ) );
		ui.originalVideoLabel->setPixmap( originalImagePixmap );
		ui.originalVideoLabel->setMaximumHeight( originalImagePixmap.width() );
		ui.originalVideoLabel->setMaximumWidth( originalImagePixmap.height() );
		ui.originalVideoLabel->adjustSize();
		timer.stop();
		timer.store();
		//std::cout << "it took by average:" << timer.getAverageTimeStdString() << "ms." << std::endl;
		//std::cout << "lates was: " << timer.getLatestStdString() << "ms." << std::endl;
		QString elapsed;
		elapsed.append( QString( "%1" ).arg( videoReader.getNormalizedProgress() ) );

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

void BachelorThesis::openSampleFile( void )
{
	std::string fileName = "G:\\DB\\Dropbox\\BA\\code\\BachelorThesis\\BachelorThesis\\Fri_Oct_11_compilation.mp4";

	videoReader.open( fileName );
	ui.progressBarSlider->setMaximum( videoReader.getMaxFrames() );

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

void BachelorThesis::openVideoStream( void )
{
	std::string null = "";
	videoReader.open( null );
}
