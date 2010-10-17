#include "Color.h"

namespace Baluchon { namespace Core { namespace Data {

CColor::CColor(void)
{
}


CColor::~CColor(void)
{
}

void CColor::setRGB(CvScalar color) {
	mRGB = color;
}

void CColor::setRGB(int r, int g, int b) {
	setRGB(cvScalar(r, g, b));
}

void CColor::setHSV(CvScalar color) {
	mHSV = color;
}

void CColor::setHSV(int h, int s, int v) {
	setHSV(cvScalar(h, s, v));
}

CvScalar CColor::getRGB(void) {
	return mRGB;
}

CvScalar CColor::getHSV(void) {
	return mHSV;
}

}}};