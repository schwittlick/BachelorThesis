#include "BachelorThesis.h"

#include "QTimer"
#include "QFileDialog"

BachelorThesis::BachelorThesis(QWidget *parent)
	: QMainWindow(parent),
	videoReader( VideoReader::Type::CPU ),
	playbackSpeed( 1 )
{
	ui.setupUi(this);

	timer = Timer();	

	connect( ui.actionOpen_File, SIGNAL( triggered() ), this, SLOT( openFile() ) );
	connect( ui.verticalSlider, SIGNAL( valueChanged( int ) ), this, SLOT( changePlaybackSpeed( int ) ) );
	connect( ui.pushButton, SIGNAL( clicked() ), this, SLOT( startVideo() ) );
	connect( ui.progressBarSlider, SIGNAL( valueChanged( int) ), this, SLOT( jumpToFrame( int ) ) );
}

BachelorThesis::~BachelorThesis()
{

}

void BachelorThesis::loadImage() 
{
	if( videoReader.isOpen() )
	{
		timer.start();
		cv::Mat loadedImage = videoReader.getNextImage();

		for( int i = 0; i < playbackSpeed; i++ ) 
		{
			loadedImage = videoReader.getNextImage();
		}
		
		cv::imshow( "VIDEO_CPU", loadedImage );
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
	timer->start( 100 );

	ui.pushButton->setText( QString( "Pause" ) );
}

void BachelorThesis::jumpToFrame( int _frameNr )
{
	videoReader.jumpToFrame( _frameNr );
}
