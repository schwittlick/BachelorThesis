#include "BachelorThesis.h"
#include "src/misc/SystemInfo.h"

#include <thread>

#include "QTimer"
#include "QFileDialog"

BachelorThesis::BachelorThesis(QWidget *parent)
	: QMainWindow(parent),
	videoReader( VideoReader::Type::CPU ),
	playbackSpeed( 1 ),
	doBackgroundSubtraction( false ),
	blurAmount( 1 )
{
	ui.setupUi(this);

	timer = Timer();	

	lukasKanadeOpticalFlowDialog = new LukasKanadeOpticalFLowDialog( this );


	cv::gpu::DeviceInfo info( 0 );

	std::cout << "Currently available GPU devices: " << SystemInfo::getAvailableCudaDeviceCount() << " " << info.name() << std::endl;
	
	cv::gpu::setDevice( 0 );

	connect( ui.actionOpen_File,			SIGNAL( triggered() ),				this,	SLOT( openFile() ) );
	connect( ui.verticalSlider,				SIGNAL( valueChanged( int ) ),		this,	SLOT( changePlaybackSpeed( int ) ) );
	connect( ui.pushButton,					SIGNAL( clicked() ),				this,	SLOT( startVideo() ) );
	connect( ui.progressBarSlider,			SIGNAL( valueChanged( int) ),		this,	SLOT( jumpToFrame( int ) ) );
	connect( ui.radioButton,				SIGNAL( toggled( bool ) ),			this,	SLOT( toggleBackgroundSubtraction( bool ) ) );
	connect( ui.blurSlider,					SIGNAL( valueChanged( int ) ),		this,	SLOT( blurAmountChanged( int ) ) );
	connect( ui.actionOpen_Sample,			SIGNAL( triggered() ),				this,	SLOT( openSampleFile() ) );
	
	connect( ui.actionPyrLukasKanade,		SIGNAL( triggered() ),				this,	SLOT( openLukasKanadeWindow( ) ) );

	connect( lukasKanadeOpticalFlowDialog,	SIGNAL( itersValueChanged( int ) ), this,	SLOT( changeLKIters( int ) ) );
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
		cv::Mat imageToProcess = loadedImage->clone();

		for( int i = 0; i < playbackSpeed; i++ )
		{
			loadedImage = videoReader.getNextImage();
			imageToProcess = loadedImage->clone();
		}

		if( doBackgroundSubtraction )
		{
			bg.applyBGS( &imageToProcess, BackgroundSubtractor::Type::MOG2 );
		}

		MeanShifter::Type meanShifterType = MeanShifter::FILTERING_GPU;
		meanshifter.applyMeanShift( &imageToProcess, meanShifterType );

		//Denoiser::applyDenoise( &imageToProcess, 1 );

		//Blur::applyBlur( Blur::Type::NORMAL, &imageToProcess, 10 );

		//cv::Mat * flow = new cv::Mat();

		//flow = lkflow.apply( &imageToProcess, false );
		
		//cv::imshow( "FLOW", *flow );
		cv::imshow( "VIDEO_CPU", imageToProcess );
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

	cv::namedWindow( "VIDEO_CPU", cv::WINDOW_NORMAL );
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
	this->lkflow.setIters( _iters );
}

void BachelorThesis::changeLKWinSize( int _winSize )
{
	std::cout << "LKOF: winSize: " << _winSize << std::endl;
	this->lkflow.setWinSize( _winSize );
}

void BachelorThesis::changeLKMaxlevel( int _maxLevel )
{
	std::cout << "LKOF: maxLevel: " << _maxLevel << std::endl;
	this->lkflow.setMaxLevel( _maxLevel );
}

void BachelorThesis::openSampleFile( void )
{
	cv::namedWindow( "VIDEO_CPU", cv::WINDOW_NORMAL );
	cv::namedWindow( "FLOW", cv::WINDOW_NORMAL );

	std::string fileName = "G:\\DB\\Dropbox\\BA\\code\\BachelorThesis\\BachelorThesis\\Fri_Oct_11_compilation.mp4";

	videoReader.open( fileName );
	ui.progressBarSlider->setMaximum( videoReader.getMaxFrames() );

	bg = BackgroundSubtractor();
}
