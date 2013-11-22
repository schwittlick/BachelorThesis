#include "FrameHandler.h"


FrameHandler::FrameHandler(void)
{
}


FrameHandler::~FrameHandler(void)
{
}

void FrameHandler::createNewOutput( std::string name, int id, int type )
{
	cv::namedWindow( name, type );
	windowMap[ id ] = name;
}

void FrameHandler::display( cv::gpu::GpuMat * im, int id )
{
	cv::imshow( windowMap.find( id )->second, *im );
}

void FrameHandler::closeWindow( int id )
{
	cv::destroyWindow( windowMap.find( id )->second );
}

void FrameHandler::closeAllWindows( void )
{
	for( auto it = windowMap.begin(); it != windowMap.end(); ++it )
	{
		this->closeWindow( it->first );
	}
}
