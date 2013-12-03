#pragma once

#include < vector >

#include "QObject"
#include "QDialog"

#include "opencv2/core/core.hpp"
#include "opencv2/gpu/gpu.hpp"

#include "FeatureDetector.h"
#include "src/ip/StandardImageProcessor.h"
#include "OpticalFlowFarneback.h"
#include "OpticalFlowLukaskanade.h"
#include "OpticalFlowSF.h"
#include "DualTVL1OpticalFlow.h"

#include "ProcessingStep.h"

#include "imageprocessorwidget.h"

#include "src/opticalflow/LukasKanadeOpticalFlow.h"

#include "QWidget"
#include "QObject"

class ProcessingPipeline : public QWidget
{
	Q_OBJECT
public:
	ProcessingPipeline( QWidget *parent = 0 );
	~ProcessingPipeline(void);

	void addImage( cv::gpu::GpuMat * imageToBeProcessed );
	void start( void );
	cv::gpu::GpuMat getFinishedImage( void );

public slots:
	void checkBoxClicked( int id );
	void downClicked( int id );
	void upClicked( int id );
	void configClicked( int id );
	void toggleLukasKanadeDialogDisplay( void );
signals:
	void toggleDialogDisplay( void );

private:
	cv::gpu::GpuMat currentImage;
	FeatureDetector fea;
	StandardImageProcessor improc;
	OpticalFlowFarneback flowFarneback;
	OpticalFlowLukaskanade flowKanade;
	OpticalFlowSF flowSF;
	DualTVL1OpticalFlow flowTvl1;

	LukasKanadeOpticalFlow flowKanadeGPU;

	std::vector< ProcessingStep * > processingSteps;

	ImageProcessorWidget * imageProcessorWidget;
	

	int minSurfaceArea;

	bool checkSize( cv::gpu::GpuMat * image );
};

