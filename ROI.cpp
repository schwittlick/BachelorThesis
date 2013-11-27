#include "ROI.h"


ROI::ROI(void)
{
}


ROI::~ROI(void)
{
}

void ROI::setRoi( float x, float y, float w, float h )
{
	this->roi = QRectF( x, y, w, h );
}

void ROI::setRoi( QRectF r )
{
	this->roi = r;
}
