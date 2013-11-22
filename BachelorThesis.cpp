#include "BachelorThesis.h"
#include "src/misc/SystemInfo.h"

#include <thread>

#include "QTimer"
#include "QFileDialog"

BachelorThesis::BachelorThesis(QWidget *parent)
	: QMainWindow(parent),
	videoReader( VideoReader::Type::GPU ),
	playbackSpeed( 1 ),
	doBackgroundSubtraction( false ),
	doMeanShiftFiltering( false ),
	blurAmount( 1 )
{
	ui.setupUi(this);

	timer = Timer();	

	lukasKanadeOpticalFlowDialog = new LukasKanadeOpticalFLowDialog( this );
	hardwareInfoDialog = new HardwareInfoDialog( this );
	
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
}

void BachelorThesis::loadImage() 
{
	if( videoReader.isOpen() )
	{
		timer.start();
		cv::gpu::GpuMat * imageToProcess;
		cv::gpu::GpuMat finishedImage;

		for( int i = 0; i < playbackSpeed; i++ )
		{
			imageToProcess = videoReader.getNextImage_GPU();
		}

		pipeline.addImage( imageToProcess );
		pipeline.start();
		finishedImage = pipeline.getFinishedImage();

		frameHandler.display( &finishedImage, 0 );

		timer.stop();
		timer.store();
		std::cout << "it took by average:" << timer.getAverageTimeStdString() << "ms." << std::endl;
		std::cout << "lates was: " << timer.getLatestStdString() << "ms." << std::endl;
		QString elapsed;
		elapsed.append( QString( "%1" ).arg( videoReader.getNormalizedProgress() ) );

		ui.label->setText( elapsed );
		ui.progressBarSlider->setValue( videoReader.getCurrentFrameNr() );
	}
	else
	{
		// if the file/stream is not opened then all windows should be closed
		frameHandler.closeAllWindows();
	}
}

void BachelorThesis::openFile( void )
{
	QString fileName = QFileDialog::getOpenFileName( this, tr( "Open File" ), "", tr( "MP4 (*.mp4);; AVI (*.avi)" ) );

	frameHandler.createNewOutput( "VIDEO_GPU", 0, cv::WINDOW_OPENGL );

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

	ui.pushButton->setText( QString( "Pause" ) );
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
	frameHandler.createNewOutput( "VIDEO_GPU", 0, cv::WINDOW_OPENGL );

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
