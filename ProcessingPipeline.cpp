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
	processingPipelineConfigWidget = new ImageProcessorWidget( this );

	connect( processingPipelineConfigWidget,			SIGNAL( checkBoxClicked( int ) ),		this,	SLOT( checkBoxClicked( int ) ) );
	connect( processingPipelineConfigWidget,			SIGNAL( upButtonClicked( int ) ),		this,	SLOT( upClicked( int ) ) );
	connect( processingPipelineConfigWidget,			SIGNAL( downButtonClicked( int ) ),		this,	SLOT( downClicked( int ) ) );
	connect( processingPipelineConfigWidget,			SIGNAL( configButtonClicked( int ) ),	this,	SLOT( configClicked( int ) ) );
	connect( this,										SIGNAL( toggleDialogDisplay() ),		this,	SLOT( toggleLukasKanadeDialogDisplay() ) );


	currentProcessingStepOrder.push_back( 0 );
	currentProcessingStepOrder.push_back( 1 );
	currentProcessingStepOrder.push_back( 2 );
	currentProcessingStepOrder.push_back( 3 );
	currentProcessingStepOrder.push_back( 4 );
	currentProcessingStepOrder.push_back( 5 );
	currentProcessingStepOrder.push_back( 6 );
	currentProcessingStepOrder.push_back( 7 );
	currentProcessingStepOrder.push_back( 8 );
	currentProcessingStepOrder.push_back( 9 );
	currentProcessingStepOrder.push_back( 10 );

	//printCurrentprocessingOrder();


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
	delete processingPipelineConfigWidget;
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
	bool doBM = true;
	if( doBM )
	{
		//bm.apply( &currentImage );
	}
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

void ProcessingPipeline::toggleProcessingPipelineConfigWidgetDisplay( void )
{
	if( this->processingPipelineConfigWidget->isVisible() )
	{
		this->processingPipelineConfigWidget->close();
	}
	else
	{
		this->processingPipelineConfigWidget->show();
	}
}

void ProcessingPipeline::downClicked( int id )
{
	if( id < 10 )
	{
		int actualID = findId( currentProcessingStepOrder, id );
		int oneButtonDownID = actualID + 1;
		std::swap( currentProcessingStepOrder[ actualID ], currentProcessingStepOrder[ oneButtonDownID ] );
		actualID = getActualID( actualID );
		oneButtonDownID = getActualID( oneButtonDownID );
		
		QPushButton * clickedButtonDown = processingPipelineConfigWidget->getDownButtonById( actualID);
		QRect tempPosDown = clickedButtonDown->geometry();
		QPushButton * toSwapWithButtonDown = processingPipelineConfigWidget->getDownButtonById( oneButtonDownID );
		clickedButtonDown->setGeometry( toSwapWithButtonDown->geometry() );
		toSwapWithButtonDown->setGeometry( tempPosDown );
		// swap the up button position
		QPushButton * clickedButtonUp = processingPipelineConfigWidget->getUpButtonByID( actualID );
		QRect tempPosUp = clickedButtonUp->geometry();
		QPushButton * toSwapWithButtonUp = processingPipelineConfigWidget->getUpButtonByID( oneButtonDownID );
		clickedButtonUp->setGeometry( toSwapWithButtonUp->geometry() );
		toSwapWithButtonUp->setGeometry( tempPosUp );
		// swap labels
		QLabel * clickedLabel = processingPipelineConfigWidget->getLabelByID( actualID );
		QRect tempPosLabel = clickedLabel->geometry();
		QLabel * toSwapWithLabel = processingPipelineConfigWidget->getLabelByID( oneButtonDownID );
		clickedLabel->setGeometry( toSwapWithLabel->geometry() );
		toSwapWithLabel->setGeometry( tempPosLabel );
		// config button
		QPushButton * clickedButtonConfig = processingPipelineConfigWidget->getConfigButtonByID( actualID );
		QRect tempPosConfig = clickedButtonConfig->geometry();
		QPushButton * toSwapWithButtonConfig = processingPipelineConfigWidget->getConfigButtonByID( oneButtonDownID );
		clickedButtonConfig->setGeometry( toSwapWithButtonConfig->geometry() );
		toSwapWithButtonConfig->setGeometry( tempPosConfig );
		// checkbox
		QCheckBox * clickedCheckBox = processingPipelineConfigWidget->getCheckBoxByID( actualID );
		QRect tempPosCheckbox = clickedCheckBox->geometry();
		QCheckBox * toSwapWithCheckbox = processingPipelineConfigWidget->getCheckBoxByID( oneButtonDownID );
		clickedCheckBox->setGeometry( toSwapWithCheckbox->geometry() );
		toSwapWithCheckbox->setGeometry( tempPosCheckbox );
		
		//printCurrentprocessingOrder( id );
	}
}

void ProcessingPipeline::upClicked( int id )
{
	if( id > 0)
	{
		int actualID = findId( currentProcessingStepOrder, id );
		int oneButtonUpID = actualID - 1;
		std::swap( currentProcessingStepOrder[ actualID ], currentProcessingStepOrder[ oneButtonUpID ] );
		actualID = getActualID( actualID );
		oneButtonUpID = getActualID( oneButtonUpID );
		// swap the down button positions
		QPushButton * clickedButtonDown = processingPipelineConfigWidget->getDownButtonById( actualID );
		QRect tempPosDown = clickedButtonDown->geometry();
		QPushButton * toSwapWithButtonDown = processingPipelineConfigWidget->getDownButtonById( oneButtonUpID );
		clickedButtonDown->setGeometry( toSwapWithButtonDown->geometry() );
		toSwapWithButtonDown->setGeometry( tempPosDown );
		// swap the up button position
		QPushButton * clickedButtonUp = processingPipelineConfigWidget->getUpButtonByID( actualID );
		QRect tempPosUp = clickedButtonUp->geometry();
		QPushButton * toSwapWithButtonUp = processingPipelineConfigWidget->getUpButtonByID( oneButtonUpID );
		clickedButtonUp->setGeometry( toSwapWithButtonUp->geometry() );
		toSwapWithButtonUp->setGeometry( tempPosUp );
		// swap labels
		QLabel * clickedLabel = processingPipelineConfigWidget->getLabelByID( actualID );
		QRect tempPosLabel = clickedLabel->geometry();
		QLabel * toSwapWithLabel = processingPipelineConfigWidget->getLabelByID( oneButtonUpID );
		clickedLabel->setGeometry( toSwapWithLabel->geometry() );
		toSwapWithLabel->setGeometry( tempPosLabel );
		// config button
		QPushButton * clickedButtonConfig = processingPipelineConfigWidget->getConfigButtonByID( actualID );
		QRect tempPosConfig = clickedButtonConfig->geometry();
		QPushButton * toSwapWithButtonConfig = processingPipelineConfigWidget->getConfigButtonByID( oneButtonUpID );
		clickedButtonConfig->setGeometry( toSwapWithButtonConfig->geometry() );
		toSwapWithButtonConfig->setGeometry( tempPosConfig );
		// checkbox
		QCheckBox * clickedCheckBox = processingPipelineConfigWidget->getCheckBoxByID( actualID );
		QRect tempPosCheckbox = clickedCheckBox->geometry();
		QCheckBox * toSwapWithCheckbox = processingPipelineConfigWidget->getCheckBoxByID( oneButtonUpID );
		clickedCheckBox->setGeometry( toSwapWithCheckbox->geometry() );
		toSwapWithCheckbox->setGeometry( tempPosCheckbox );
	}
}

void ProcessingPipeline::configClicked( int id )
{
	std::cout << "Config clicked for " << id << std::endl;
	processingSteps.at( id )->toggleConfigWindow();
}

int ProcessingPipeline::getActualID( int _id )
{
	return currentProcessingStepOrder[ _id ];
}

int ProcessingPipeline::findId( const std::vector<int>& where, int searchParameter )
{
	for( int i = 0; i < where.size(); i++ ) {
		if( where[i] == searchParameter )
		{
			return i;
		}
	}
	return -1;
}