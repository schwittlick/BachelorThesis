#include "SystemInfo.h"


SystemInfo::SystemInfo(void)
{
}


SystemInfo::~SystemInfo(void)
{
}

int SystemInfo::getAvailableCudaDeviceCount( void )
{
	return cv::gpu::getCudaEnabledDeviceCount();
}
