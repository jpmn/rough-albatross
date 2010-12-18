#pragma once

#include <cv.h>
#include <vector>

using namespace std;

namespace baluchon { namespace core { namespace datas { namespace detection {

class IFacet
{
public:
	virtual ~IFacet(void) {}

	virtual CvPoint getCenterPosition(void) = 0;

	static bool sortByX(CvPoint pt1, CvPoint pt2) {
		return pt1.x < pt2.x;
	}

	static bool sortByY(CvPoint pt1, CvPoint pt2) {
		return pt1.y < pt2.y;
	}
};

}}}};