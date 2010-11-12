#include "ColorUtility.h"

#include "MathUtility.h"

namespace baluchon { namespace utilities {

CvScalar ColorUtility::convertRGB2HSV(CvScalar rgb) {
	return ColorUtility::convertRGB2HSV(rgb.val[0], rgb.val[1], rgb.val[2]);
}

CvScalar ColorUtility::convertRGB2HSV(int r, int g, int b) {

	int minRGB = MathUtility::min(r, g, b);
	int maxRGB = MathUtility::max(r, g, b);
	
	int v = maxRGB;

	if (v == 0)
		return cvScalar(0, 0, 0);

	int s = 255 * (maxRGB - minRGB) / v;
	
	if (s == 0)
		return cvScalar(0, 0, 0);

	int h = 0;

	if (maxRGB == r) {
		h = 0 + 43 * (g - b) / (maxRGB - minRGB);
	} 
	else if (maxRGB == g) {
		h = 85 + 43 * (b - r) / (maxRGB - minRGB);
	} 
	else /* maxRGB == b */ {
		h = 171 + 43 * (r - g) / (maxRGB - minRGB);
	}

	return cvScalar(h, s, v);
}

CvScalar ColorUtility::convertHSV2RGB(CvScalar hsv) {
	return ColorUtility::convertHSV2RGB(hsv.val[0], hsv.val[1], hsv.val[2]);
}


CvScalar ColorUtility::convertHSV2RGB(int h, int s, int v) {
	
    if (s == 0)
		return cvScalar(v, v, v);

	int f = ((h % 60) * 255) / 60;

    h /= 60;
 
    long p = (v * (256 - s)) / 256;
	long q = (v * (256 - (s * f) / 256)) / 256;
    long t = (v * (256 - (s * (256 - f)) / 256)) / 256;
 
    switch (h) {
		case 0:
			return cvScalar(v, t, p);
        case 1:
			return cvScalar(q, v, p);
        case 2:
			return cvScalar(p, v, t);
        case 3:
			return cvScalar(p, q, v);
        case 4:
			return cvScalar(t, p, v);
        default:
			return cvScalar(v, p, q);
	}
}

void convertRGB2HSV(Mat* rgb, Mat* hsv) {
	int nb = hsv->channels();

	for (unsigned int y = 0; y < rgb->rows; y++) {
		for (unsigned int x = 0; x < rgb->cols; x++) {
			int r = rgb->ptr<int>(y)[nb * x + 1];
			int g = rgb->ptr<int>(y)[nb * x + 2];
			int b = rgb->ptr<int>(y)[nb * x + 3];
		
			CvScalar colorHSV = ColorUtility::convertHSV2RGB(r, g, b);

			hsv->ptr<int>(y)[nb * x + 1] = colorHSV.val[0];
			hsv->ptr<int>(y)[nb * x + 2] = colorHSV.val[1];
			hsv->ptr<int>(y)[nb * x + 3] = colorHSV.val[2];
		}
	}
}

void convertHSV2RGB(Mat* hsv, Mat* rgb) {
	int nb = hsv->channels();

	for (unsigned int y = 0; y < hsv->rows; y++) {
		for (unsigned int x = 0; x < hsv->cols; x++) {
			int h = hsv->ptr<int>(y)[nb * x + 1];
			int s = hsv->ptr<int>(y)[nb * x + 2];
			int v = hsv->ptr<int>(y)[nb * x + 3];
		
			CvScalar colorRGB = ColorUtility::convertRGB2HSV(h, s, v);

			rgb->ptr<int>(y)[nb * x + 1] = colorRGB.val[0];
			rgb->ptr<int>(y)[nb * x + 2] = colorRGB.val[1];
			rgb->ptr<int>(y)[nb * x + 3] = colorRGB.val[2];
		}
	}
}

}};