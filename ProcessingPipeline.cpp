#include "ProcessingPipeline.h"


ProcessingPipeline::ProcessingPipeline(void)
{
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
	cv::Mat im;
	this->currentImage.download( im );

	bgs.applyBGS( &currentImage, BackgroundSubtractor::Type::MOG2 );

	improc.makeBinary( &this->currentImage );

	//fea.processGoodFeaturesToTrack_CPU( &im );

	//flowFarneback.calc( &im );

	//currentImage.upload( im );

	//fea.processHOGDetection_GPU( &currentImage );
}

cv::gpu::GpuMat ProcessingPipeline::getFinishedImage( void )
{
	return this->currentImage;
}
