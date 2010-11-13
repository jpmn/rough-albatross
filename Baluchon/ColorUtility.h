#pragma once

#include <cv.h>

using namespace cv;

namespace baluchon { namespace utilities {

class ColorUtility
{
public:
	static CvScalar convertColorBGRtoHSV(CvScalar bgr);
	static CvScalar convertColorBGRtoHSV(int b, int g, int r);
	static CvScalar convertColorHSVtoBGR(CvScalar hsv);
	static CvScalar convertColorHSVtoBGR(int h, int s, int v);
	static void convertImageBGRtoHSV(IplImage* imageBGR, IplImage* imageHSV);
	static void convertImageHSVtoBGR(IplImage* imageHSV, IplImage* imageBGR);

private:
	ColorUtility(void) {};
	~ColorUtility(void) {};
};

}};