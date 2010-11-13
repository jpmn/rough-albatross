#include "ColorUtility.h"

#include "MathUtility.h"

namespace baluchon { namespace utilities {

CvScalar ColorUtility::convertColorBGRtoHSV(CvScalar bgr) {
	return ColorUtility::convertColorBGRtoHSV(bgr.val[0], bgr.val[1], bgr.val[2]);
}

CvScalar ColorUtility::convertColorBGRtoHSV(int b, int g, int r) {

	// Convert from 8-bit integers to floats.
	float fH, fS, fV;
	const float FLOAT_TO_BYTE = 255.0f;
	const float BYTE_TO_FLOAT = 1.0f / FLOAT_TO_BYTE;

	float fR = r * BYTE_TO_FLOAT;
	float fG = g * BYTE_TO_FLOAT;
	float fB = b * BYTE_TO_FLOAT;

	// Convert from RGB to HSV, using float ranges 0.0 to 1.0.
	float fDelta;
	float fMin, fMax;
	int iMax;

	// Get the min and max, but use integer comparisons for slight speedup.
	if (b < g) {
		if (b < r) {
			fMin = fB;

			if (r > g) { iMax = r; fMax = fR; }
			else { iMax = g; fMax = fG; }
		}
		else { fMin = fR; fMax = fG; iMax = g; }
	}
	else {
		if (b < r) {
			fMin = fG;

			if (b > r) { fMax = fB; iMax = b; }
			else { fMax = fR; iMax = r; }
		}
		else { fMin = fR; fMax = fB; iMax = b; }
	}
	fDelta = fMax - fMin;
	fV = fMax;				// Value (Brightness).
	if (iMax != 0) {			// Make sure its not pure black.
		fS = fDelta / fMax;		// Saturation.
		float ANGLE_TO_UNIT = 1.0f / (6.0f * fDelta);	// Make the Hues between 0.0 to 1.0 instead of 6.0
		if (iMax == r) {		// between yellow and magenta.
			fH = (fG - fB) * ANGLE_TO_UNIT;
		}
		else if (iMax == g) {		// between cyan and yellow.
			fH = (2.0f/6.0f) + ( fB - fR ) * ANGLE_TO_UNIT;
		}
		else {				// between magenta and cyan.
			fH = (4.0f/6.0f) + ( fR - fG ) * ANGLE_TO_UNIT;
		}
		// Wrap outlier Hues around the circle.
		if (fH < 0.0f)	fH += 1.0f;
		if (fH >= 1.0f)	fH -= 1.0f;
	}
	else {
		// color is pure Black.
		fS = 0;
		fH = 0;	// undefined hue
	}

	// Convert from floats to 8-bit integers.
	int bH = (int)(0.5f + fH * 255.0f);
	int bS = (int)(0.5f + fS * 255.0f);
	int bV = (int)(0.5f + fV * 255.0f);

	// Clip the values to make sure it fits within the 8bits.
	if (bH > 255)	bH = 255;
	if (bH < 0)		bH = 0;
	if (bS > 255)	bS = 255;
	if (bS < 0)		bS = 0;
	if (bV > 255)	bV = 255;
	if (bV < 0)		bV = 0;

	return cvScalar(bH, bS, bV);
}

CvScalar ColorUtility::convertColorHSVtoBGR(CvScalar hsv) {
	return ColorUtility::convertColorHSVtoBGR(hsv.val[0], hsv.val[1], hsv.val[2]);
}


CvScalar ColorUtility::convertColorHSVtoBGR(int h, int s, int v) {
	
    // Convert from 8-bit integers to floats
	float fR, fG, fB;
	const float FLOAT_TO_BYTE = 255.0f;
	const float BYTE_TO_FLOAT = 1.0f / FLOAT_TO_BYTE;

	float fH = (float)h * BYTE_TO_FLOAT;
	float fS = (float)s * BYTE_TO_FLOAT;
	float fV = (float)v * BYTE_TO_FLOAT;

	// Convert from HSV to RGB, using float ranges 0.0 to 1.0
	int iI;
	float fI, fF, p, q, t;

	if( s == 0 ) {
		// achromatic (grey)
		fR = fG = fB = fV;
	}
	else {
		// If Hue == 1.0, then wrap it around the circle to 0.0
		if (fH >= 1.0f)
			fH = 0.0f;

		fH *= 6.0;			// sector 0 to 5
		fI = floor( fH );		// integer part of h (0,1,2,3,4,5 or 6)
		iI = (int) fH;			//		"		"		"		"
		fF = fH - fI;			// factorial part of h (0 to 1)

		p = fV * ( 1.0f - fS );
		q = fV * ( 1.0f - fS * fF );
		t = fV * ( 1.0f - fS * ( 1.0f - fF ) );

		switch( iI ) {
			case 0: fR = fV; fG = t; fB = p;
				break;
			case 1: fR = q; fG = fV; fB = p;
				break;
			case 2: fR = p; fG = fV; fB = t;
				break;
			case 3: fR = p; fG = q; fB = fV;
				break;
			case 4: fR = t; fG = p; fB = fV;
				break;
			default: fR = fV; fG = p; fB = q; // case 5 (or 6):
				break;
		}
	}

	// Convert from floats to 8-bit integers
	int bR = (int)(fR * FLOAT_TO_BYTE);
	int bG = (int)(fG * FLOAT_TO_BYTE);
	int bB = (int)(fB * FLOAT_TO_BYTE);

	// Clip the values to make sure it fits within the 8bits.
	if (bR > 255)	bR = 255;
	if (bR < 0)		bR = 0;
	if (bG > 255)	bG = 255;
	if (bG < 0)		bG = 0;
	if (bB > 255)	bB = 255;
	if (bB < 0)		bB = 0;

	return cvScalar(bB, bG, bR);
}

// Create a HSV image from the RGB image using the full 8-bits, since OpenCV only allows Hues up to 180 instead of 255.
// ref: "http://cs.haifa.ac.il/hagit/courses/ist/Lectures/Demos/ColorApplet2/t_convert.html"
// Remember to free the generated HSV image.
void ColorUtility::convertImageBGRtoHSV(IplImage *imageRGB, IplImage* imageHSV)
{
	float fR, fG, fB;
	float fH, fS, fV;
	const float FLOAT_TO_BYTE = 255.0f;
	const float BYTE_TO_FLOAT = 1.0f / FLOAT_TO_BYTE;

	int h = imageRGB->height;		// Pixel height.
	int w = imageRGB->width;		// Pixel width.
	int rowSizeRGB = imageRGB->widthStep;	// Size of row in bytes, including extra padding.
	char *imRGB = imageRGB->imageData;	// Pointer to the start of the image pixels.
	int rowSizeHSV = imageHSV->widthStep;	// Size of row in bytes, including extra padding.
	char *imHSV = imageHSV->imageData;	// Pointer to the start of the image pixels.
	for (int y=0; y<h; y++) {
		for (int x=0; x<w; x++) {
			// Get the RGB pixel components. NOTE that OpenCV stores RGB pixels in B,G,R order.
			uchar *pRGB = (uchar*)(imRGB + y*rowSizeRGB + x*3);
			int bB = *(uchar*)(pRGB+0);	// Blue component
			int bG = *(uchar*)(pRGB+1);	// Green component
			int bR = *(uchar*)(pRGB+2);	// Red component

			CvScalar colorHSV = ColorUtility::convertColorBGRtoHSV(bB, bG, bR);

			// Set the HSV pixel components.
			uchar *pHSV = (uchar*)(imHSV + y*rowSizeHSV + x*3);
			*(pHSV+0) = colorHSV.val[0];		// H component
			*(pHSV+1) = colorHSV.val[1];		// S component
			*(pHSV+2) = colorHSV.val[2];		// V component
		}
	}
}


// Create an RGB image from the HSV image using the full 8-bits, since OpenCV only allows Hues up to 180 instead of 255.
// ref: "http://cs.haifa.ac.il/hagit/courses/ist/Lectures/Demos/ColorApplet2/t_convert.html"
// Remember to free the generated RGB image.
void ColorUtility::convertImageHSVtoBGR(IplImage *imageHSV, IplImage* imageRGB)
{
	float fH, fS, fV;
	float fR, fG, fB;
	const float FLOAT_TO_BYTE = 255.0f;
	const float BYTE_TO_FLOAT = 1.0f / FLOAT_TO_BYTE;

	int h = imageHSV->height;			// Pixel height.
	int w = imageHSV->width;			// Pixel width.
	int rowSizeHSV = imageHSV->widthStep;		// Size of row in bytes, including extra padding.
	char *imHSV = imageHSV->imageData;		// Pointer to the start of the image pixels.
	int rowSizeRGB = imageRGB->widthStep;		// Size of row in bytes, including extra padding.
	char *imRGB = imageRGB->imageData;		// Pointer to the start of the image pixels.
	for (int y=0; y<h; y++) {
		for (int x=0; x<w; x++) {
			// Get the HSV pixel components
			uchar *pHSV = (uchar*)(imHSV + y*rowSizeHSV + x*3);
			int bH = *(uchar*)(pHSV+0);	// H component
			int bS = *(uchar*)(pHSV+1);	// S component
			int bV = *(uchar*)(pHSV+2);	// V component

			CvScalar colorBGR = ColorUtility::convertColorHSVtoBGR(bH, bS, bV);

			// Set the RGB pixel components. NOTE that OpenCV stores RGB pixels in B,G,R order.
			uchar *pRGB = (uchar*)(imRGB + y*rowSizeRGB + x*3);
			*(pRGB+0) = colorBGR.val[0];		// B component
			*(pRGB+1) = colorBGR.val[1];		// G component
			*(pRGB+2) = colorBGR.val[2];		// R component
		}
	}
}

}};