#pragma once

#include <opencv2/gpu/gpu.hpp>

class SystemInfo
{
public:
	SystemInfo(void);
	~SystemInfo(void);

	static int getAvailableCudaDeviceCount( void );
};

