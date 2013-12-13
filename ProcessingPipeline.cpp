#include "ProcessingPipeline.h"

#include "src/ip/steps/MedianFilterStep.h"
#include "src/ip/steps/BackgroundSubtractionStep.h"
#include "src/ip/steps/DilationStep.h"
#include "src/ip/steps/ErosionStep.h"
#include "src/ip/steps/OpenStep.h"
#include "src/ip/steps/CloseStep.h"
#include "src/ip/steps/TopHatStep.h"
#include "src/ip/steps/BlackHatStep.h"
#include "src/ip/steps/GradientStep.h"
#include "src/ip/steps/GaussianBlurStep.h"
#include "src/ip/steps/BiliteralFilterStep.h"
#include "src/ip/steps/ThresholdStep.h"

#include <algorithm>

ProcessingPipeline::ProcessingPipeline( QWidget *parent ) : 
	QWidget( parent ),
	minSurfaceArea( 2000 )
{
	processingPipelineConfigWidget = new ImageProcessorWidget( this );
	opticalflowSelectorDialog = new OpticalFlowSelectorDialog( this );

	blob = new BlobDetector();

	connect( processingPipelineConfigWidget,			SIGNAL( checkBoxClicked( int ) ),		this,	SLOT( checkBoxClicked( int ) ) );
	connect( processingPipelineConfigWidget,			SIGNAL( upButtonClicked( int ) ),		this,	SLOT( upClicked( int ) ) );
	connect( processingPipelineConfigWidget,			SIGNAL( downButtonClicked( int ) ),		this,	SLOT( downClicked( int ) ) );
	connect( processingPipelineConfigWidget,			SIGNAL( configButtonClicked( int ) ),	this,	SLOT( configClicked( int ) ) );
	connect( this,										SIGNAL( toggleDialogDisplay() ),		this,	SLOT( toggleLukasKanadeDialogDisplay() ) );

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
	processingSteps.push_back( new ThresholdStep() );

	// initializes the standard order
	for( int i = 0; i < processingSteps.size(); ++i )
	{
		currentProcessingStepOrder.push_back( i );
	}

	// adding some optical flow methods to the container
	opticalFlows.push_back( new OpticalFlowFarneback() );

	// connecting the functionality from the flowselector to the corresponding flow
	//connect( opticalflowSelectorDialog, SIGNAL( lukasKanadeActivated() ), ( QObject* )flowFarneback, SIGNAL( activate() ) );
	connect( opticalflowSelectorDialog, SIGNAL( farnebackActivated() ), ( QWidget* ) opticalFlows.at( 0 ), SLOT( activate() ) );
	connect( opticalflowSelectorDialog, SIGNAL( farnebackDialogToggled() ), ( QWidget* ) opticalFlows.at( 0 ), SLOT( toggleConfigWindow() ) );
	//connect( opticalflowSelectorDialog, SIGNAL( blockMatchingActivated() ), ( QObject* )flowFarneback, SIGNAL( activate() ) );
	//connect( opticalflowSelectorDialog, SIGNAL( broxActivated() ), ( QObject* )flowFarneback, SIGNAL( activate() ) );
	//connect( opticalflowSelectorDialog, SIGNAL( dualTVL1Activated() ), ( QObject* )flowFarneback, SIGNAL( activate() ) );
	//connect( opticalflowSelectorDialog, SIGNAL( hsActivated() ), ( QObject* )flowFarneback, SIGNAL( activate() ) );

	
}

ProcessingPipeline::~ProcessingPipeline(void)
{
	delete processingPipelineConfigWidget;
	delete opticalflowSelectorDialog;

	for( auto it = processingSteps.begin(); it != processingSteps.end(); ++it )
	{
		delete *it;
	}

	for( auto it = opticalFlows.begin(); it != opticalFlows.end(); ++it )
	{
		delete *it;
	}
}

void ProcessingPipeline::addImage( cv::gpu::GpuMat * imageToBeProcessed )
{
	imageToBeProcessed->copyTo( this->currentImage );
}

void ProcessingPipeline::start( void )
{
	if( checkSize( &currentImage ) )
	{
		// doing some image processing
		for( int i = 0; i < processingSteps.size(); i++ )
		{
			// does the imageprocessing in the selected order. phew.
			processingSteps.at( currentProcessingStepOrder[ i ] )->apply( &currentImage );
		}

		//doing some optical flow calculation
		for( auto it = opticalFlows.begin(); it != opticalFlows.end(); ++it )
		{
			( *it )->apply( &currentImage );
		}
	}

	bool doBlobDetec = false;
	if( doBlobDetec )
	{
		// this should be done on a b/w image
		cv::Mat im;
		currentImage.download( im );
		blob->detect( &im );
		currentImage.upload( im );
	}
	// median filter, block matching
	// geschwindigkeitsberechnung anhand von 2 linien
	// meanshift filtering
	// pyrup, pyrdown
	bool doKanade = false;
	if( doKanade )
	{
		flowKanadeGPU->apply( &currentImage );
	}

	bool doGpuBlur = false;
	if( doGpuBlur )
	{
		cv::gpu::blur( currentImage, currentImage, cv::Size( 3, 3 ), cv::Point( -1, -1 ) );
	}

	//flowKanade.calc( &im );
	bool doBM = false;
	if( doBM )
	{
		bm->apply( &currentImage );
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
	flowKanadeGPU->toggleViewDisplay();
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
	if( !isVeryBottomElement( id ) )
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
	if( !isVeryTopElement( id ) )
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

bool ProcessingPipeline::isVeryBottomElement( int _id )
{
	return ( findId( currentProcessingStepOrder, _id ) < currentProcessingStepOrder.size() - 1 ) ? false : true;
}

bool ProcessingPipeline::isVeryTopElement( int _id )
{
	return ( findId( currentProcessingStepOrder, _id ) > 0 ) ? false : true;
}

void ProcessingPipeline::toggleOpticalFlowSelectorDialog( void )
{
	opticalflowSelectorDialog->setVisible( !opticalflowSelectorDialog->isVisible() );
}
