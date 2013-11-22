#pragma once

#include < string >
#include < map >
#include < iostream >

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/gpu/gpu.hpp"

class FrameHandler
{
public:
	FrameHandler(void);
	~FrameHandler(void);

	void createNewOutput( std::string name, int id, int type );
	void display(cv::gpu::GpuMat * im, int id );
	void closeWindow( int id );
	void closeAllWindows( void );

private:
	std::map< int, std::string > windowMap;
};

