#include "ProcessingStep.h"


ProcessingStep::ProcessingStep(void) :
	activated( false ),
	kernelSize( 3 )
{
	this->setKernelSize( kernelSize );
}


ProcessingStep::~ProcessingStep(void)
{
}

void ProcessingStep::toggle()
{
	this->activated = !this->activated;
}

bool ProcessingStep::isActive( void )
{
	return this->activated;
}

void ProcessingStep::setKernelSize( int _kernelSize )
{
	this->kernelSize = _kernelSize;
	kernel = cv::getStructuringElement( 0, cv::Size( 2 * kernelSize + 1, 2 * kernelSize + 1 ), cv::Point( kernelSize, kernelSize ) );

}

cv::Mat ProcessingStep::getKernel()
{
	return kernel;
}

int ProcessingStep::getKernelSize( void )
{
	return kernelSize;
}
