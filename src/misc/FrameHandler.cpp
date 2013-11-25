#include "FrameHandler.h"


FrameHandler::FrameHandler(void)
{
}


FrameHandler::~FrameHandler(void)
{
}

void FrameHandler::createNewOutput( std::string name, int id, int type )
{
	std::cout << "windowMap size: " << windowMap.size() << std::endl;
	cv::namedWindow( name, type );
	windowMap[ id ] = name;
	std::cout << "FrameHandler::createNewOutput " << name << " " << type << std::endl;
	std::cout << "windowMap size: " << windowMap.size() << std::endl;
}

void FrameHandler::display( cv::gpu::GpuMat * im, int id )
{
	cv::imshow( windowMap.find( id )->second, *im );
}

void FrameHandler::closeWindow( int id )
{
	std::cout << "windowMap size: " << windowMap.size() << std::endl;
	cv::destroyWindow( windowMap.find( id )->second );
	windowMap.erase( id );
	std::cout << "FrameHandler::closeWindow " << std::endl;
	std::cout << "windowMap size: " << windowMap.size() << std::endl;
}

void FrameHandler::closeAllWindows( void )
{
	for( auto it = windowMap.begin(); it != windowMap.end(); ++it )
	{
		this->closeWindow( it->first );
	}
}
