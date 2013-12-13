#pragma once

#include < vector >
#include < map >
#include < memory >

//#include <boost/spirit.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include "QObject"
#include "QDialog"

#include "opencv2/core/core.hpp"
#include "opencv2/gpu/gpu.hpp"

#include "src/detect/FeatureDetector.h"
#include "src/ip/StandardImageProcessor.h"
#include "src/opticalflow/OpticalFlowFarneback.h"
#include "src/opticalflow/OpticalFlowLukaskanade.h"
#include "src/opticalflow/OpticalFlowSF.h"
#include "src/opticalflow/DualTVL1OpticalFlow.h"
#include "src/opticalflow/OpticalFlowBlockMatching.h"

#include "src/ip/steps/ProcessingStep.h"
#include "src/detect/BlobDetector.h"

#include "imageprocessorwidget.h"
#include "src/opticalflow/dialogs/OpticalFlowSelectorDialog.h"

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
	void toggleProcessingPipelineConfigWidgetDisplay( void );
	void toggleOpticalFlowSelectorDialog( void );
	void checkBoxClicked( int id );
	void downClicked( int id );
	void upClicked( int id );
	void configClicked( int id );
	void toggleLukasKanadeDialogDisplay( void );
signals:
	void toggleDialogDisplay( void );

private:
	cv::gpu::GpuMat currentImage;
	FeatureDetector * fea;
	StandardImageProcessor improc;
	OpticalFlowLukaskanade * flowKanade;
	OpticalFlowSF * flowSF;
	DualTVL1OpticalFlow * flowTvl1;
	OpticalFlowBlockMatching * bm;
	LukasKanadeOpticalFlow * flowKanadeGPU;
	BlobDetector * blob;

	std::vector< ProcessingStep * > processingSteps;
	std::vector< int > currentProcessingStepOrder;
	int getActualID( int _id );
	int findId( const std::vector<int>& where, int searchParameter );

	std::vector< OpticalFlowMethod * > opticalFlows;

	OpticalFlowSelectorDialog * opticalflowSelectorDialog;
	ImageProcessorWidget * processingPipelineConfigWidget;

	int minSurfaceArea;

	bool checkSize( cv::gpu::GpuMat * image );

	bool isVeryBottomElement( int _id );
	bool isVeryTopElement( int _id );
};

