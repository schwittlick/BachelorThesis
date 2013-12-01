#include "ProcessingPipeline.h"

ProcessingPipeline::ProcessingPipeline() : 
	minSurfaceArea( 2000 )
{

	doImageProcessingTask.push_back( false );
	doImageProcessingTask.push_back( false );
	doImageProcessingTask.push_back( false );
	doImageProcessingTask.push_back( false );
	doImageProcessingTask.push_back( false );
	doImageProcessingTask.push_back( false );
	doImageProcessingTask.push_back( false );
	std::cout << "doImageProcessingTask.size=" << doImageProcessingTask.size() << std::endl;
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
	//bgs.applyBGS( &currentImage, BackgroundSubtractor::Type::MOG2 );
	//this->currentImage.download( im );

	//improc.makeBinary( &this->currentImage );

	//fea.processGoodFeaturesToTrack_CPU( &im );
	//cv::Mat im;
	//currentImage.download( im );
	//flowFarneback.calc( &im );
	//currentImage.upload( im );
	//flowKanade.calc( &im );

	flowKanadeGPU.apply( &currentImage );

	//cv::Mat flow;
	//flowKanadeGPU.apply( &currentImage );
	
	//flowKanade.calc( &im );
	//std::cout << "startin." << std::endl;
	//flowSF.calc( &im );
	//cv::Mat flow;
	cv::gpu::GpuMat flowGpu;
	
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
