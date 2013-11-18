#include "Denoiser.h"


Denoiser::Denoiser(void)
{
}


Denoiser::~Denoiser(void)
{
}

void Denoiser::applyDenoise( cv::Mat * image, int amount )
{
	for( int i = 0; i < amount; i++ )
	{
		cv::fastNlMeansDenoisingColored( *image, *image, 7, 21, 10, 10 );
	}
	
}
