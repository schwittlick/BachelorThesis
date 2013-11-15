#include "BachelorThesis.h"

#include "QTimer"
#include "QFileDialog"

BachelorThesis::BachelorThesis(QWidget *parent)
	: QMainWindow(parent),
	videoReader( VideoReader::Type::CPU )
{
	ui.setupUi(this);

	timer = Timer();

	QTimer * timer = new QTimer( this );
	connect( timer, SIGNAL( timeout() ), this, SLOT(loadImage() ) );
	timer->start( 100 );

	connect( ui.actionOpen_File, SIGNAL( triggered() ), this, SLOT( openFile() ) );


	std::cout << "QTimer started..";
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
		loadedImage = videoReader.getNextImage();
		loadedImage = videoReader.getNextImage();
		loadedImage = videoReader.getNextImage();
		loadedImage = videoReader.getNextImage();
		loadedImage = videoReader.getNextImage();
		cv::imshow( "VIDEO_CPU", loadedImage );
		timer.stop();
		QString elapsed;
		elapsed.append( QString( "%1" ).arg( timer.getLatest() ) );
		ui.label->setText( elapsed );
	}
}

void BachelorThesis::openFile( void )
{
	QString fileName = QFileDialog::getOpenFileName( this, tr( "Open File" ), "", tr( "MP4 (*.mp4);; AVI (*.avi)" ) );
	//cvStartWindowThread();
	cv::namedWindow("VIDEO_CPU", cv::WINDOW_NORMAL );
	videoReader.open( fileName.toStdString() );
}