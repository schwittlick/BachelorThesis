#pragma once

#include < iostream >
#include < vector >

#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/gpu/gpu.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/objdetect/objdetect.hpp>

#include "src/detect/BlobDetector.h"

class StandardImageProcessor
{
public:
	StandardImageProcessor(void);
	~StandardImageProcessor(void);

	void makeBinary( cv::gpu::GpuMat * gpuImage );
	BlobDetector det;
	std::vector< cv::KeyPoint > points;
};

