#pragma once

#include < iostream >
#include < vector >

#include "opencv2/gpu/gpu.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "src/detect/BlobDetector.h"

class StandardImageProcessor
{
public:
	StandardImageProcessor(void);
	~StandardImageProcessor(void);

	static void makeBinary( cv::gpu::GpuMat * gpuImage );
};

