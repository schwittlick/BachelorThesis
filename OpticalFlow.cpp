#include "OpticalFlow.h"


OpticalFlow::OpticalFlow( QWidget *parent ) :
	QWidget( parent )
{
}


OpticalFlow::~OpticalFlow(void)
{
}

void OpticalFlow::toggleConfigWindow( void )
{
	std::cout << "OpticalFlow::toggleConfigWindow base class called." << std::endl;
}

void OpticalFlow::apply( cv::gpu::GpuMat * image )
{
	std::cout << "OpticalFlow::apply base class called." << std::endl;
}

void OpticalFlow::activate( void )
{
	std::cout << "OpticalFlow::activate base class called." << std::endl;
}
