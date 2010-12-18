#pragma once

#include <cv.h>

namespace baluchon { namespace utilities {

class MathUtility
{
public:
	//static const float PI = 3.14159265;
	//static const float HALF_PI = 1.57079633;
	//static const float TWO_PI = 6.28318531;

	template <typename T>
	static T min(T n1, T n2, T n3) {
		return std::min(n1, std::min(n2, n3));
	}

	template <typename T>
	static T max(T n1, T n2, T n3) {
		return std::max(n1, std::max(n2, n3));
	}

	static CvPoint middle(CvPoint pt1, CvPoint pt2) {
		int dx = pt1.x + pt2.x;
		int dy = pt1.y + pt2.y;

		return cvPoint((pt1.x + pt2.x)/2, (pt1.y + pt2.y)/2);
	}

	static double distance(CvPoint pt1, CvPoint pt2) {
		return ((pt1.x - pt2.x) * (pt1.x - pt2.x)) + ((pt1.y - pt2.y) * (pt1.y - pt2.y));
	}

	static double sqrtdistance(CvPoint pt1, CvPoint pt2) {
		return std::sqrt(std::pow((double)pt1.x - pt2.x, 2) + std::pow((double)pt1.y - pt2.y, 2));
	}

	static double angle(CvPoint* pt0, CvPoint* pt1, CvPoint* pt2) {
 
		double dx1 = pt1->x - pt0->x; 
		double dy1 = pt1->y - pt0->y; 
		double dx2 = pt2->x - pt0->x; 
		double dy2 = pt2->y - pt0->y; 

		return (dx1*dx2 + dy1*dy2) / std::sqrt((dx1*dx1 + dy1*dy1) * (dx2*dx2 + dy2*dy2) + 1e-10); 
	}

	static CvPoint intersect(CvPoint line1Pt1, CvPoint line1Pt2, CvPoint line2Pt1, CvPoint line2Pt2) {

		/*
			a = (yB - yA) / (xB - xA)
			b = yA - a * xA

			y = a.x + b

			xi = (b1 - b2) / (a2 - a1)
			yi = a1.xi + b1
		*/
		
		float a1 = (float)(line1Pt2.y - line1Pt1.y) / (line1Pt2.x - line1Pt1.x);
		float b1 = (line1Pt1.y - (a1 * line1Pt1.x));

		float a2 = (float)(line2Pt2.y - line2Pt1.y) / (line2Pt2.x - line2Pt1.x);
		float b2 = (line2Pt1.y - (a2 * line2Pt1.x));
		
		int x = (b1 - b2) / (a2 - a1);
		int y = (a1 * x) + b1;
		
		return cvPoint(x, y);
	}
};

}};