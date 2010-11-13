#pragma once

#include <cv.h>

using namespace cv;

namespace baluchon { namespace utilities {

class ColorUtility
{
public:
	static CvScalar convertRGB2HSV(CvScalar rgb);
	static CvScalar convertRGB2HSV(int r, int g, int b);
	static CvScalar convertHSV2RGB(CvScalar rgb);
	static CvScalar convertHSV2RGB(int h, int s, int v);
	static void convertImageRGBtoHSV(IplImage* imageRGB, IplImage* imageHSV);
	static void convertImageHSVtoRGB(IplImage* imageHSV, IplImage* imageRGB);

private:
	ColorUtility(void) {};
	~ColorUtility(void) {};
};

}};