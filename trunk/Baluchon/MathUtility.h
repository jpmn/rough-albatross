#pragma once

#include <cv.h>
#include "Face.h"

using namespace baluchon::core::services::objectdetection;

namespace baluchon { namespace utilities {

class MathUtility
{
public:
	template <typename T>
	static T min(T n1, T n2, T n3) {
		return std::min(n1, std::min(n2, n3));
	}

	template <typename T>
	static T max(T n1, T n2, T n3) {
		return std::max(n1, std::max(n2, n3));
	}

	static double findAngle(CvPoint* pt0, CvPoint* pt1, CvPoint* pt2);
	static CvPoint findIntersectionPoint(CvPoint pt0, CvPoint pt1, double intersect);
	static double findDistance(CvPoint pt0, CvPoint pt1, CvPoint pt2);
	static double findDistance(CvPoint pt0, CvPoint pt1);
	static bool sortByDistanceFromOrigin(const CvPoint& pt0, const CvPoint& pt1);
	static bool sortByX(const CvPoint& pt0, const CvPoint& pt1);
	static bool sortByCenterPositionX(Face* f0, Face* f1);
	static bool sortByY(const CvPoint& pt0, const CvPoint& pt1);
	static bool sortByCenterPositionY(Face* f0, Face* f1);

private:
	MathUtility(void) {};
	~MathUtility(void) {};
};

}};