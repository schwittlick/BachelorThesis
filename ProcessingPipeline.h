#pragma once

#include < vector >

#include "QObject"
#include "QDialog"

#include "opencv2/core/core.hpp"
#include "opencv2/gpu/gpu.hpp"

#include "FeatureDetector.h"
#include "src/ip/StandardImageProcessor.h"
#include "src/ip/BackgroundSubtractor.h"
#include "OpticalFlowFarneback.h"
#include "OpticalFlowLukaskanade.h"
#include "OpticalFlowSF.h"
#include "DualTVL1OpticalFlow.h"

#include "src/opticalflow/LukasKanadeOpticalFlow.h"



class ProcessingPipeline : QObject
{
	Q_OBJECT
public:
	ProcessingPipeline( void );
	~ProcessingPipeline(void);

	void addImage( cv::gpu::GpuMat * imageToBeProcessed );
	void start( void );
	cv::gpu::GpuMat getFinishedImage( void );

	void setTaskTodo( int taskId, bool value );
	bool getTaskTodo( int taskId );

public slots:
	void checkBoxClicked( int id );

private:
	cv::gpu::GpuMat currentImage;
	FeatureDetector fea;
	BackgroundSubtractor bgs;
	StandardImageProcessor improc;
	OpticalFlowFarneback flowFarneback;
	OpticalFlowLukaskanade flowKanade;
	OpticalFlowSF flowSF;
	DualTVL1OpticalFlow flowTvl1;

	LukasKanadeOpticalFlow flowKanadeGPU;
	

	int minSurfaceArea;

	bool checkSize( cv::gpu::GpuMat * image );

	std::vector< bool > doImageProcessingTask;
};

