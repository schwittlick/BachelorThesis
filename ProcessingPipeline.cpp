#include "ProcessingPipeline.h"

ProcessingPipeline::ProcessingPipeline() : 
	minSurfaceArea( 2000 )
{
	/*
	doImageProcessingTask.assign( 0, false );
	doImageProcessingTask.assign( 1, false );
	doImageProcessingTask.assign( 2, false );
	doImageProcessingTask.assign( 3, false );
	doImageProcessingTask.assign( 4, false );
	doImageProcessingTask.assign( 5, false );
	doImageProcessingTask.assign( 6, false );
	*/
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
		//improc.binary( &currentImage, 100 );
		//improc.erode( &currentImage );
		//improc.topHat( &currentImage );
		//improc.open( &currentImage, 2 );
		//improc.gradient( &currentImage );
		//improc.topHat( &currentImage, 10 );
		//bgs.applyBGS( &currentImage, BackgroundSubtractor::Type::MOG2 );
	}
	//bgs.applyBGS( &currentImage, BackgroundSubtractor::Type::MOG2 );
	//this->currentImage.download( im );

	//improc.makeBinary( &this->currentImage );

	//fea.processGoodFeaturesToTrack_CPU( &im );

	//flowFarneback.calc( &im );
	//flowKanade.calc( &im );
	//std::cout << "startin." << std::endl;
	//flowSF.calc( &im );
	//cv::Mat flow;
	//cv::gpu::GpuMat flowGpu;
	//flow = flowKanadeGPU.apply( &im, false );
	//flow = flowTvl1.calc( &im );
	//flowGpu = flowTvl1.calcGPU( &currentImage );

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
