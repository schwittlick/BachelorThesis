#pragma once

#include <stdio.h>
#include <iostream>
#include <string>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/gpu/gpu.hpp"
#include <opencv2/contrib/contrib.hpp>
#include <opencv2/core/opengl_interop.hpp>


class VideoReader
{
public:
	enum Type { CPU, GPU } selectedType;

	VideoReader( enum Type type );
	~VideoReader( void );

	void open( std::string fileName );
	void close( void );
	bool isOpen( void );
	cv::Mat getNextImage( void );
	double getNormalizedProgress( void );
	int getMaxFrames( void );
	int getCurrentFrameNr( void );
	void jumpToFrame( int _frameNr );
	bool isFinished( void );

private:
	cv::Mat currentFrame;
	cv::Mat emptyMat;
	cv::gpu::GpuMat currentGpuMat;
	bool wasOpened;

	int maxFrameCount, currentFrameNr;

	int widthLoadedVideo, heightLoadedVideo;

	cv::VideoCapture videoCapture;
	cv::gpu::VideoReader_GPU videoReaderGPU;
};
