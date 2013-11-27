#pragma once

#include "QRectF"

class ROI
{
public:
	ROI(void);
	~ROI(void);

	void setRoi( float x, float y, float w, float h );
	void setRoi( QRectF r );

private:
	QRectF roi;
};

