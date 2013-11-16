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

	maxFrameCount = videoCapture.get( CV_CAP_PROP_FRAME_COUNT );
	currentFrameNr = 0;

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
			currentFrameNr = videoCapture.get( CV_CAP_PROP_POS_FRAMES );
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
		if( videoReaderGPU.isOpened() )
		{
			currentFrameNr++;
			videoReaderGPU.read( currentGpuMat );
			cv::Mat fr( currentGpuMat );
			fr.copyTo( currentFrame );
		}
		else
		{
			std::cout << "VideoCapture is not opened." << std::endl;
			currentFrame = emptyMat;
		}

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

double VideoReader::getNormalizedProgress( void )
{
	double progressNormalized;

	progressNormalized = currentFrameNr / ( double )( maxFrameCount );

	return progressNormalized;
}

int VideoReader::getMaxFrames( void )
{
	return maxFrameCount;
}

int VideoReader::getCurrentFrameNr( void )
{
	return currentFrameNr;
}

void VideoReader::jumpToFrame( int _frameNr )
{
	switch( selectedType )
	{
	case CPU:
		videoCapture.set( CV_CAP_PROP_POS_FRAMES, ( double ) _frameNr );
		break;
	case GPU:
		std::cerr << "Can't jump frames when using GPU VideoReader. Doing nothing instead." << std::endl;
		break;
	}
}
