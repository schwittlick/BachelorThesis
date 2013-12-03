#include "ProcessingPipeline.h"
#include "MedianFilterStep.h"
#include "BackgroundSubtractionStep.h"
#include "DilationStep.h"
#include "ErosionStep.h"
#include "OpenStep.h"
#include "CloseStep.h"
#include "TopHatStep.h"
#include "BlackHatStep.h"
#include "GradientStep.h"
#include "GaussianBlurStep.h"
#include "BiliteralFilterStep.h"

#include <algorithm>

ProcessingPipeline::ProcessingPipeline( QWidget *parent ) : 
	QWidget( parent ),
	minSurfaceArea( 2000 ),
	flowKanadeGPU( parent )
{
	imageProcessorWidget = new ImageProcessorWidget( this );
	imageProcessorWidget->show();

	connect( imageProcessorWidget,			SIGNAL( checkBoxClicked( int ) ),	this,	SLOT( checkBoxClicked( int ) ) );
	connect( imageProcessorWidget,			SIGNAL( upButtonClicked( int ) ),	this,	SLOT( upClicked( int ) ) );
	connect( imageProcessorWidget,			SIGNAL( downButtonClicked( int ) ),	this,	SLOT( downClicked( int ) ) );
	connect( imageProcessorWidget,			SIGNAL( configButtonClicked( int ) ),	this,	SLOT( configClicked( int ) ) );
	connect( this, SIGNAL( toggleDialogDisplay() ), this, SLOT( toggleLukasKanadeDialogDisplay() ) );

	processingSteps.push_back( new DilationStep( ) );
	processingSteps.push_back( new ErosionStep() );
	processingSteps.push_back( new OpenStep() );
	processingSteps.push_back( new CloseStep() );
	processingSteps.push_back( new TopHatStep() );
	processingSteps.push_back( new BlackHatStep() );
	processingSteps.push_back( new GradientStep() );

	processingSteps.push_back( new MedianFilterStep() );
	processingSteps.push_back( new BackgroundSubtractionStep() );
	processingSteps.push_back( new GaussianBlurStep() );
	processingSteps.push_back( new BiliteralFilterStep() );
	//std::swap( processingSteps.begin() + 1, processingSteps.begin() );
}

ProcessingPipeline::~ProcessingPipeline(void)
{
	delete imageProcessorWidget;
}

void ProcessingPipeline::addImage( cv::gpu::GpuMat * imageToBeProcessed )
{
	imageToBeProcessed->copyTo( this->currentImage );
}

void ProcessingPipeline::start( void )
{
	if( checkSize( &currentImage ) )
	{
		for( auto it = processingSteps.begin(); it != processingSteps.end(); ++it )
		{
			( *it )->apply( &currentImage );
		}
	}

	//
	
	bool doFarneback = false;
	if( doFarneback )
	{
		cv::Mat im;
		currentImage.download( im );
		flowFarneback.calc( &im );
		currentImage.upload( im );
	}
	// median filter, block matching
	// geschwindigkeitsberechnung anhand von 2 linien
	// meanshift filtering
	// pyrup, pyrdown
	bool doKanade = false;
	if( doKanade )
	{
		flowKanadeGPU.apply( &currentImage );
	}
	bool doSmooth = false;
	if( doSmooth )
	{
		// doesnt work
		cv::Mat im;
		currentImage.download( im );
		cvSmooth( &im.data, &im.data );
		currentImage.upload( im );
	}

	bool doGpuBlur = false;
	if( doGpuBlur )
	{
		cv::gpu::blur( currentImage, currentImage, cv::Size( 3, 3 ), cv::Point( -1, -1 ) );
	}

	//bgs.applyBGS( &currentImage, BackgroundSubtractor::Type::MOG2 );

	//flowKanade.calc( &im );


	//cv::Mat flow;
	//flowKanadeGPU.apply( &currentImage );
	
	//flowKanade.calc( &im );
	//std::cout << "startin." << std::endl;
	//flowSF.calc( &im );
	//cv::Mat flow;
	
	//flow = flowTvl1.calc( &im );
	//flowGpu = flowTvl1.calcGPU( &currentImage );
	//flowGpu.copyTo( currentImage );

	//std::cout << "finished." << std::endl;

	//flowGpu.copyTo( currentImage );

	//currentImage.upload( flow );

	//fea.processHOGDetection_GPU( &currentImage );
}

cv::gpu::GpuMat ProcessingPipeline::getFinishedImage( void )
{
	return this->currentImage;
}

bool ProcessingPipeline::checkSize( cv::gpu::GpuMat * image )
{
	int currentImageSurfaceArea = image->cols * image->rows;
	if( currentImageSurfaceArea >= minSurfaceArea && image->rows > 20 && image->cols > 20 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ProcessingPipeline::checkBoxClicked( int id )
{
	//setTaskTodo( id, !getTaskTodo( id ) );
	processingSteps.at( id )->toggle( );
}

void ProcessingPipeline::toggleLukasKanadeDialogDisplay( void )
{
	flowKanadeGPU.toggleViewDisplay();
}

void ProcessingPipeline::downClicked( int id )
{
	if( id <= 10 )
	{
		// swapping functionality in this class
		std::swap( processingSteps.begin() + id, processingSteps.begin() + ( id + 1 ) );
		// swap the down button positions
		QPushButton * clickedButtonDown = imageProcessorWidget->getDownButtonById( id );
		QRect tempPosDown = clickedButtonDown->geometry();
		QPushButton * toSwapWithButtonDown = imageProcessorWidget->getDownButtonById( id + 1 );
		clickedButtonDown->setGeometry( toSwapWithButtonDown->geometry() );
		toSwapWithButtonDown->setGeometry( tempPosDown );
		// swap the up button position
		QPushButton * clickedButtonUp = imageProcessorWidget->getUpButtonByID( id );
		QRect tempPosUp = clickedButtonUp->geometry();
		QPushButton * toSwapWithButtonUp = imageProcessorWidget->getUpButtonByID( id + 1 );
		clickedButtonUp->setGeometry( toSwapWithButtonUp->geometry() );
		toSwapWithButtonUp->setGeometry( tempPosUp );
		// swap labels
		QLabel * clickedLabel = imageProcessorWidget->getLabelByID( id );
		QRect tempPosLabel = clickedLabel->geometry();
		QLabel * toSwapWithLabel = imageProcessorWidget->getLabelByID( id + 1 );
		clickedLabel->setGeometry( toSwapWithLabel->geometry() );
		toSwapWithLabel->setGeometry( tempPosLabel );
		// config button
		QPushButton * clickedButtonConfig = imageProcessorWidget->getConfigButtonByID( id );
		QRect tempPosConfig = clickedButtonConfig->geometry();
		QPushButton * toSwapWithButtonConfig = imageProcessorWidget->getConfigButtonByID( id + 1 );
		clickedButtonConfig->setGeometry( toSwapWithButtonConfig->geometry() );
		toSwapWithButtonConfig->setGeometry( tempPosConfig );
		// checkbox
		QCheckBox * clickedCheckBox = imageProcessorWidget->getCheckBoxByID( id );
		QRect tempPosCheckbox = clickedCheckBox->geometry();
		QCheckBox * toSwapWithCheckbox = imageProcessorWidget->getCheckBoxByID( id + 1 );
		clickedCheckBox->setGeometry( toSwapWithCheckbox->geometry() );
		toSwapWithCheckbox->setGeometry( tempPosCheckbox );
	}
}

void ProcessingPipeline::upClicked( int id )
{
	if( id >= 1)
	{
		// swapping functionality in this class
		std::swap( processingSteps.begin() + id, processingSteps.begin() + ( id - 1 ) );
		// swap the down button positions
		QPushButton * clickedButtonDown = imageProcessorWidget->getDownButtonById( id );
		QRect tempPosDown = clickedButtonDown->geometry();
		QPushButton * toSwapWithButtonDown = imageProcessorWidget->getDownButtonById( id - 1 );
		clickedButtonDown->setGeometry( toSwapWithButtonDown->geometry() );
		toSwapWithButtonDown->setGeometry( tempPosDown );
		// swap the up button position
		QPushButton * clickedButtonUp = imageProcessorWidget->getUpButtonByID( id );
		QRect tempPosUp = clickedButtonUp->geometry();
		QPushButton * toSwapWithButtonUp = imageProcessorWidget->getUpButtonByID( id +-1 );
		clickedButtonUp->setGeometry( toSwapWithButtonUp->geometry() );
		toSwapWithButtonUp->setGeometry( tempPosUp );
		// swap labels
		QLabel * clickedLabel = imageProcessorWidget->getLabelByID( id );
		QRect tempPosLabel = clickedLabel->geometry();
		QLabel * toSwapWithLabel = imageProcessorWidget->getLabelByID( id - 1 );
		clickedLabel->setGeometry( toSwapWithLabel->geometry() );
		toSwapWithLabel->setGeometry( tempPosLabel );
		// config button
		QPushButton * clickedButtonConfig = imageProcessorWidget->getConfigButtonByID( id );
		QRect tempPosConfig = clickedButtonConfig->geometry();
		QPushButton * toSwapWithButtonConfig = imageProcessorWidget->getConfigButtonByID( id - 1 );
		clickedButtonConfig->setGeometry( toSwapWithButtonConfig->geometry() );
		toSwapWithButtonConfig->setGeometry( tempPosConfig );
		// checkbox
		QCheckBox * clickedCheckBox = imageProcessorWidget->getCheckBoxByID( id );
		QRect tempPosCheckbox = clickedCheckBox->geometry();
		QCheckBox * toSwapWithCheckbox = imageProcessorWidget->getCheckBoxByID( id - 1 );
		clickedCheckBox->setGeometry( toSwapWithCheckbox->geometry() );
		toSwapWithCheckbox->setGeometry( tempPosCheckbox );
	}
}

void ProcessingPipeline::configClicked( int id )
{
	//processingSteps.at( id )->toggleConfigWindow();
}
