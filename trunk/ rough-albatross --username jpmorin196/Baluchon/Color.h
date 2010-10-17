#pragma once

#include <cv.h>

namespace Baluchon { namespace Core { namespace Data {

class CColor
{
public:
	CColor(void);
	~CColor(void);

	void setRGB(CvScalar color);
	void setRGB(int r, int g, int b);
	void setHSV(CvScalar color);
	void setHSV(int h, int s, int v);

	CvScalar getRGB(void);
	CvScalar getHSV(void);

private:
	CvScalar mRGB;
	CvScalar mHSV;
};

}}};