#include "ProcessingPipeline.h"

ProcessingPipeline::ProcessingPipeline( QWidget *parent ) : 
	QWidget( parent ),
	minSurfaceArea( 2000 ),
	flowKanadeGPU( parent )

{
	doImageProcessingTask.push_back( false );
	doImageProcessingTask.push_back( false );
	doImageProcessingTask.push_back( false );
	doImageProcessingTask.push_back( false );
	doImageProcessingTask.push_back( false );
	doImageProcessingTask.push_back( false );
	doImageProcessingTask.push_back( false );
	std::cout << "doImageProcessingTask.size=" << doImageProcessingTask.size() << std::endl;

	//connect( this, SIGNAL( openLukasKanadeConfig() ), ( QWidget * )  flowKanadeGPU , SLOT( openConfig() ) );
	//connect( this, SIGNAL( closeLukasKanadeConfig() ), ( QWidget * )  flowKanadeGPU , SLOT( closeConfig() ) );
	connect( this, SIGNAL( toggleDialogDisplay() ), this, SLOT( toggleLukasKanadeDialogDisplay() ) );

}

ProcessingPipeline::~ProcessingPipeline(void)
{
}

void ProcessingPipeline::addImage( cv::gpu::GpuMat * imageToBeProcessed )
{
	imageToBeProcessed->copyTo( this->currentImage );
}

void ProcessingPipeline::start( void )
{
	if( checkSize( &currentImage ) )
	{

		if( getTaskTodo( 0 ) )
		{
			improc.dilate( &currentImage );
		}
		if( getTaskTodo( 1 ) )
		{
			improc.erode( &currentImage );
		}
		if( getTaskTodo( 2 ) )
		{
			improc.open( &currentImage );
		}
		if( getTaskTodo( 3 ) )
		{
			improc.close( &currentImage );
		}
		if( getTaskTodo( 4 ) )
		{
			improc.topHat( &currentImage );
		}
		if( getTaskTodo( 5 ) )
		{
			improc.blackHat( &currentImage );
		}
		if( getTaskTodo( 6 ) )
		{
			improc.gradient( &currentImage );
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


	bool doMedian = false;
	if( doMedian )
	{
		cv::Mat im;
		currentImage.download( im );
		cv::medianBlur( im, im, 11 );
		
		currentImage.upload( im );
	}

	bool doGaussianBlur = false;
	if( doGaussianBlur )
	{
		cv::gpu::GaussianBlur( currentImage, currentImage, cv::Size( 13, 13 ), 0 );
	}

	bool doBiliteralFilter = false;
	if( doBiliteralFilter )
	{
		cv::Mat im;
		currentImage.download( im );
		cv::cvtColor( im, im, CV_BGRA2GRAY );
		cv::Mat out;
		cv::bilateralFilter( im, out, 0, 171, 3, 0 );
		cv::cvtColor( out, out, CV_GRAY2BGRA );
		currentImage.upload( out );
	}

	bool doGpuBlur = true;
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

void ProcessingPipeline::setTaskTodo( int taskId, bool value )
{
	doImageProcessingTask[ taskId ] = value;
}

bool ProcessingPipeline::getTaskTodo( int taskId )
{
	return doImageProcessingTask[ taskId ];
}

void ProcessingPipeline::checkBoxClicked( int id )
{
	setTaskTodo( id, !getTaskTodo( id ) );
}

void ProcessingPipeline::toggleLukasKanadeDialogDisplay( void )
{
	flowKanadeGPU.toggleViewDisplay();
}
