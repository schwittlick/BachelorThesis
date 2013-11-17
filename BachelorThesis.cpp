#include "BachelorThesis.h"
#include "SystemInfo.h"

#include <thread>

#include "QTimer"
#include "QFileDialog"

BachelorThesis::BachelorThesis(QWidget *parent)
	: QMainWindow(parent),
	videoReader( VideoReader::Type::CPU ),
	playbackSpeed( 1 ),
	doBackgroundSubtraction( false )
{
	ui.setupUi(this);

	timer = Timer();	


	cv::gpu::DeviceInfo info( 0 );

	std::cout << "Currently available GPU devices: " << SystemInfo::getAvailableCudaDeviceCount() << " " << info.name() << std::endl;
	
	cv::gpu::setDevice( 0 );

	connect( ui.actionOpen_File, SIGNAL( triggered() ), this, SLOT( openFile() ) );
	connect( ui.verticalSlider, SIGNAL( valueChanged( int ) ), this, SLOT( changePlaybackSpeed( int ) ) );
	connect( ui.pushButton, SIGNAL( clicked() ), this, SLOT( startVideo() ) );
	connect( ui.progressBarSlider, SIGNAL( valueChanged( int) ), this, SLOT( jumpToFrame( int ) ) );
	connect( ui.radioButton, SIGNAL( toggled( bool ) ), this, SLOT( toggleBackgroundSubtraction( bool ) ) );
}

BachelorThesis::~BachelorThesis()
{

}

void BachelorThesis::loadImage() 
{
	if( videoReader.isOpen() )
	{
		timer.start();
		cv::Mat * loadedImage = videoReader.getNextImage();

		for( int i = 0; i < playbackSpeed; i++ )
		{
			loadedImage = videoReader.getNextImage();
		}

		if( doBackgroundSubtraction )
		{
			bg.applyBGS( loadedImage, BackgroundSubtractor::Type::MOG2 );
		}

		cv::Mat * flow = new cv::Mat();

		flow = lkflow.apply( loadedImage );
		
		cv::imshow( "FLOW", *flow );
		cv::imshow( "VIDEO_CPU", *loadedImage );
		timer.stop();

		QString elapsed;
		elapsed.append( QString( "%1" ).arg( videoReader.getNormalizedProgress() ) );

		ui.label->setText( elapsed );
		ui.progressBarSlider->setValue( videoReader.getCurrentFrameNr() );
	}
}

void BachelorThesis::openFile( void )
{
	QString fileName = QFileDialog::getOpenFileName( this, tr( "Open File" ), "", tr( "MP4 (*.mp4);; AVI (*.avi)" ) );
	//cvStartWindowThread();

	cv::namedWindow("VIDEO_CPU", cv::WINDOW_NORMAL );
	cv::namedWindow( "FLOW", cv::WINDOW_NORMAL );

	videoReader.open( fileName.toStdString() );
	ui.progressBarSlider->setMaximum( videoReader.getMaxFrames() );

	bg = BackgroundSubtractor();
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

	ui.pushButton->setText( QString( "Pause" ) );
}

void BachelorThesis::jumpToFrame( int _frameNr )
{
	videoReader.jumpToFrame( _frameNr );
}

void BachelorThesis::closeFrameWindow( void )
{
	std::cout << "Closing Windows." << std::endl;
	cvDestroyWindow( "VIDEO_CPU") ;
}

void BachelorThesis::toggleBackgroundSubtraction( bool _doBackgroundSubtraction )
{
	doBackgroundSubtraction = _doBackgroundSubtraction;
}
