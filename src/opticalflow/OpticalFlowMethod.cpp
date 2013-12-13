#include "OpticalFlowMethod.h"


OpticalFlowMethod::OpticalFlowMethod( QWidget *parent ) :
	QWidget( parent )
{
}


OpticalFlowMethod::~OpticalFlowMethod(void)
{
}

void OpticalFlowMethod::toggleConfigWindow( void )
{
	std::cout << "OpticalFlow::toggleConfigWindow base class called." << std::endl;
}

void OpticalFlowMethod::apply( cv::gpu::GpuMat * image )
{
	std::cout << "OpticalFlow::apply base class called." << std::endl;
}

void OpticalFlowMethod::activate( void )
{
	std::cout << "OpticalFlow::activate base class called." << std::endl;
}
