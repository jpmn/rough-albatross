#pragma once

#include "RectangularFacet.h"
#include "CircularFacet.h"

namespace baluchon { namespace core { namespace services { namespace objectdetection {

class FacetFactory
{
public:
	FacetFactory(void);
	~FacetFactory(void);

	RectangularFacet* createRectangularFacet(CvPoint pt1, CvPoint pt2, CvPoint pt3, CvPoint pt4);
	CircularFacet* createCircularFacet(CvPoint center, float radius);
};

}}}};