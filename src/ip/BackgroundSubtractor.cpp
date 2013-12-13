#include "src/ip/BackgroundSubtractor.h"


BackgroundSubtractor::BackgroundSubtractor(void) 
{
	d_fgimg.create( 10, 10, CV_8UC4 );
}


BackgroundSubtractor::~BackgroundSubtractor(void)
{
}

void BackgroundSubtractor::applyBGS( cv::Mat * image, enum Type method, double learningRate )
{
	gmg.numInitializationFrames = 40;
	image->copyTo( frame );
	d_frame.upload( frame );

	//int64 start = cv::getTickCount();

	//update the model
	switch (method)
	{
	case FGD_STAT:
		//fgd_stat.update(d_frame);
		//d_fgmask = fgd_stat.foreground;
		//d_bgimg = fgd_stat.background;
		break;

	case MOG:
		mog(d_frame, d_fgmask, learningRate);
		//mog.getBackgroundImage(d_bgimg);
		break;

	case MOG2:
		mog2(d_frame, d_fgmask, learningRate);
		//mog2.getBackgroundImage(d_bgimg);
		break;

	case GMG:
		gmg(d_frame, d_fgmask, learningRate);
		break;
	}


	d_fgimg.create(d_frame.size(), d_frame.type());
	d_fgimg.setTo(cv::Scalar::all(0));
	d_frame.copyTo(d_fgimg, d_fgmask);

	d_fgmask.download(fgmask);
	d_fgimg.download(fgimg);

	if (!d_bgimg.empty())
	{
		d_bgimg.download(bgimg);

	}

	fgimg.copyTo( *image );
}

void BackgroundSubtractor::applyBGS( cv::gpu::GpuMat * _gpu_image, enum Type method, double learningRate )
{
	gmg.numInitializationFrames = 40;
	switch ( method )
	{
	case FGD_STAT:
		//fgd_stat.update( *_gpu_image );
		//d_fgmask = fgd_stat.foreground;
		//d_bgimg = fgd_stat.background;
		break;

	case MOG:
		mog( *_gpu_image, d_fgmask, learningRate );
		//mog.getBackgroundImage( d_bgimg );
		break;

	case MOG2:
		mog2( *_gpu_image, d_fgmask, learningRate );
		//mog2.getBackgroundImage( d_bgimg );
		break;

	case GMG:
		gmg( *_gpu_image, d_fgmask );
		break;
	}

	if( d_fgimg.size() != _gpu_image->size() || d_fgimg.type() != _gpu_image->type() )
	{
		d_fgimg.create(_gpu_image->size(), _gpu_image->type());
	}

	
	d_fgimg.setTo(cv::Scalar::all(0));
	_gpu_image->copyTo(d_fgimg, d_fgmask);

	d_fgimg.copyTo( *_gpu_image );
}
