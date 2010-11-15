#include "ColorUtility.h"

#include "MathUtility.h"

namespace baluchon { namespace utilities {

CvScalar ColorUtility::convertColorBGRtoHSV(CvScalar bgr) {
	return ColorUtility::convertColorBGRtoHSV(bgr.val[0], bgr.val[1], bgr.val[2]);
}

CvScalar ColorUtility::convertColorBGRtoHSV(int ib, int ig, int ir) {
	
	float h, s, v;
	float r, g, b;

	r = ir / 255.0;
	g = ig / 255.0;
	b = ib / 255.0;

	v = MathUtility::max<float>(r, g, b);

	if (v == 0)
		s = 0;
	else
		s = (v - MathUtility::min<float>(r, g, b)) / v;

	if (v == r)
		h = 60 * (g - b) / s;
	else if (v == g)
		h = 120 + (60 * (b - r) / s);
	else // if (v == b)
		h = 240 + (60 * (r - g) / s);

	if (h < 0)
		h = h + 360;

	return cvScalar((int)(0.5 + (h / 2)), (int)(0.5 + (s * 255)), (int)(0.5 + (v * 255)));
}

CvScalar ColorUtility::convertColorHSVtoBGR(CvScalar hsv) {
	return ColorUtility::convertColorHSVtoBGR(hsv.val[0], hsv.val[1], hsv.val[2]);
}


CvScalar ColorUtility::convertColorHSVtoBGR(int ih, int is, int iv) {

	float h, s, v;
	float r, g, b;
	float f, p, q, t;
	int i;

	h = ih * 2.0;
	s = is / 255.0;
	v = iv / 255.0;

    if (s == 0) {
        r = g = b = v;
        return cvScalar((int)(0.5 + (b * 255)), (int)(0.5 + (g * 255)), (int)(0.5 + (r * 255)));
    }
   
    h /= 60;
	i = (int)std::floor(h);
    f = h - i;
    p = v * (1 - s);
    q = v * (1 - s * f);
    t = v * (1 - s * (1 - f));
   
    switch( i ) {
        case 0:		r = v; g = t; b = p;
            break;
        case 1:		r = q; g = v; b = p;
            break;
        case 2:		r = p; g = v; b = t;
            break;
        case 3:		r = p; g = q; b = v;
            break;
        case 4:		r = t; g = p; b = v;
            break;
        default:	r = v; g = p; b = q; // case 5:
            break;
    }

    return cvScalar((int)(0.5 + (b * 255)), (int)(0.5 + (g * 255)), (int)(0.5 + (r * 255)));
}

}};