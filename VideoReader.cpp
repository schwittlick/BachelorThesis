#include "VideoReader.h"


VideoReader::VideoReader( Type type ) :
	selectedType( type ),
	wasOpened( false )
{
}


VideoReader::~VideoReader(void)
{
}

void VideoReader::open( std::string fileName )
{
	videoCapture.open( fileName );
	videoReaderGPU.open( fileName );

	switch( selectedType )
	{
	case Type::CPU:
		if( videoCapture.isOpened() )
		{
			videoCapture >> currentFrame;
			widthLoadedVideo = currentFrame.size().width;
			heightLoadedVideo = currentFrame.size().height;
		}

		break;
	case Type::GPU:
		if( videoReaderGPU.isOpened() )
		{
			videoReaderGPU.read( currentGpuMat );
			widthLoadedVideo = currentGpuMat.size().width;
			heightLoadedVideo = currentGpuMat.size().height;
		}

		break;
	}

	std::cout << "VideoFile was successfully loaded with dimensions w:" << widthLoadedVideo << " h:" << heightLoadedVideo << "." << std::endl;
	emptyMat = cv::Mat::zeros( widthLoadedVideo, heightLoadedVideo, CV_8UC3 );

	wasOpened = true;
}

cv::Mat VideoReader::getNextImage( void )
{
	switch( selectedType ) 
	{
	case Type::CPU:
		if( videoCapture.isOpened() )
		{
			videoCapture >> currentFrame;
			if( currentFrame.empty() )
			{
				std::cout << "End of the videofile." << std::endl;
				currentFrame = emptyMat;
			}
		}
		else
		{
			std::cout << "VideoCapture is not opened." << std::endl;
			currentFrame = emptyMat;
		}
		break;
	case Type::GPU:
		videoReaderGPU.read( currentGpuMat );
		cv::Mat fr( currentGpuMat );
		fr.copyTo( currentFrame );
		break;
	}

	return currentFrame;
}

bool VideoReader::isOpen( void )
{
	return wasOpened;
}

void VideoReader::close( void )
{
	videoCapture.release();
	videoReaderGPU.close();

	wasOpened = false;
}
