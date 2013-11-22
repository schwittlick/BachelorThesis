#include "hardwareinfodialog.h"
#include < QString >

HardwareInfoDialog::HardwareInfoDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	cv::gpu::DeviceInfo info( 0 );

	QString graphicsCardName("");
	graphicsCardName.append( info.name().c_str() );
	ui.labelGraphics->setText( graphicsCardName );
	
	int totalMemoryInMegaBytes = info.totalMemory() / 1024 / 1024;
	std::stringstream ssTotalMemory;
	ssTotalMemory << totalMemoryInMegaBytes;
	QString qstringTotalMemory("");
	qstringTotalMemory.append( ssTotalMemory.str().c_str() );
	ui.totalMemoryLabel->setText( qstringTotalMemory );

	long usedMemoryInBytes = info.totalMemory() - info.freeMemory();
	int usedMemoryInMegaBytes = usedMemoryInBytes / 1024 / 1024;
	std::stringstream ssUsedMemory;
	ssUsedMemory << usedMemoryInMegaBytes;
	QString qstringUsedMemory("");
	qstringUsedMemory.append( ssUsedMemory.str().c_str() );
	ui.usedMemoryLabel->setText( qstringUsedMemory );

	float percentMemoryUsed = usedMemoryInMegaBytes / ( float )( totalMemoryInMegaBytes )* 100;
	QString percentMemoryUsedQString("");
	std::stringstream ss;
	ss << "" << percentMemoryUsed;
	percentMemoryUsedQString.append( ss.str().c_str() );
	ui.usedMemoryProgressBar->setValue( ( int ) ( percentMemoryUsed ) );
}

HardwareInfoDialog::~HardwareInfoDialog()
{

}
