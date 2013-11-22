#include "StandardImageProcessor.h"


StandardImageProcessor::StandardImageProcessor(void)
{
}


StandardImageProcessor::~StandardImageProcessor(void)
{
}

void StandardImageProcessor::makeBinary( cv::gpu::GpuMat * gpuImage )
{
	cv::initModule_nonfree();
	cv::Mat im;
	gpuImage->download( im );
	cv::cvtColor( im, im, CV_BGRA2GRAY );
	cv::threshold( im, im, 100, 255, 0 );
	cv::erode( im, im, cv::Mat(), cv::Point( -1, -1 ), 1, 1, 1 );
	cv::threshold( im, im, 100, 255, 0 );
	std::cout << "finished eroding, setting up blober " << std::endl;
	
	BlobDetector det;
	det.detect( &im );
	
	//std::cout << "Found " << keypoints.size() << " blobs." << std::endl;

	//cv::drawKeypoints( im, keypoints, im );

	//cv::imwrite( "image_blobbed_2.jpg", im );
	
	std::cout << "done drawing keypoints" << std::endl;
	
	/*
	//cv::cvtColor( im, im, CV_GRAY2BGR );

	std::cout << "Found " << keypoints.size() << " blobs." << std::endl;
	
	for (int i=0; i<keypoints.size(); i++){
		float X=keypoints[i].pt.x; 
		float Y=keypoints[i].pt.y;
		cv::rectangle( im, cv::Rect( X, Y, 10, 10 ), cv::Scalar( 255, 0, 0 ), 4 );
		//cv::rectangle()
	}
	//cv::imwrite( "image_blobbed.jpg", im );
	std::cout << "finished drawing blobs." << std::endl;
	
	gpuImage->upload( im );
	std::cout << "type im: " << im.type() << std::endl;

	*/
	//delete blob_detect;
	gpuImage->upload( im );
	std::cout << "Finished uploading the image back onto the gpu image." << std::endl;
	//delete blob_detect;
	std::cout << "finished deleting detector" << std::endl;
	//return im;
	//gpuImage->upload( im );
	//std::cout << "Finished uploading the image back onto the gpu image." << std::endl;

	//std::cout << "Tyoe if gpuimage: " << gpuImage->type() << std::endl;
	//cv::gpu::cvtColor( *gpuImage, *gpuImage, CV_RGBA2GRAY );
	//std::cout << "Tyoe if gpuimage: " << gpuImage->type() << std::endl;
	//cv::gpu::threshold( *gpuImage, *gpuImage, 100, cv::THRESH_BINARY, cv::THRESH_BINARY );
	//std::cout << "Finished binary." << std::endl;
}
