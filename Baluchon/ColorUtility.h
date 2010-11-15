#pragma once

#include <cv.h>

namespace baluchon { namespace utilities {

class ColorUtility
{
public:
	static CvScalar convertColorBGRtoHSV(CvScalar bgr);
	static CvScalar convertColorBGRtoHSV(int ib, int ig, int ir);
	static CvScalar convertColorHSVtoBGR(CvScalar hsv);
	static CvScalar convertColorHSVtoBGR(int ih, int is, int iv);

private:
	ColorUtility(void) {};
	~ColorUtility(void) {};
};

}};