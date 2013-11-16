#include "BackgroundSubtractor.h"


BackgroundSubtractor::BackgroundSubtractor(void) 
{
	std::cout << "BackgroundSubstractor::BackgroundSubstractor(void)" << std::endl;
}


BackgroundSubtractor::~BackgroundSubtractor(void)
{
}

void BackgroundSubtractor::applyBGS( cv::Mat & image, enum Type method )
{
	gmg.numInitializationFrames = 40;
	image.copyTo( frame );
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
		mog(d_frame, d_fgmask, 0.01f);
		mog.getBackgroundImage(d_bgimg);
		break;

	case MOG2:
		mog2(d_frame, d_fgmask);
		mog2.getBackgroundImage(d_bgimg);
		break;

	case GMG:
		gmg(d_frame, d_fgmask);
		break;
	}

	//double fps = cv::getTickFrequency() / (cv::getTickCount() - start);
	//std::cout << "FPS : " << fps << std::endl;

	d_fgimg.create(d_frame.size(), d_frame.type());
	d_fgimg.setTo(cv::Scalar::all(0));
	d_frame.copyTo(d_fgimg, d_fgmask);

	d_fgmask.download(fgmask);
	d_fgimg.download(fgimg);

	if (!d_bgimg.empty())
	{
		d_bgimg.download(bgimg);

	}

	fgimg.copyTo( image );
	//image = cv::Mat( fgimg );
}