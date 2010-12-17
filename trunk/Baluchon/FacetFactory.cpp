#include "FacetFactory.h"

#include "MathUtility.h"

using namespace baluchon::utilities;

namespace baluchon { namespace core { namespace services { namespace objectdetection {

FacetFactory::FacetFactory(void) {

}

FacetFactory::~FacetFactory(void) {

}

RectangularFacet* FacetFactory::createRectangularFacet(CvPoint pt1, CvPoint pt2, CvPoint pt3, CvPoint pt4) {
	
	vector<CvPoint> wVertices;
	wVertices.push_back(pt1);
	wVertices.push_back(pt2);
	wVertices.push_back(pt3);
	wVertices.push_back(pt4);

	std::sort(wVertices.begin(), wVertices.end(), IFacet::sortByX);
	
	RectangularFacet* facet = new RectangularFacet();

	if (wVertices[0].y < wVertices[1].y) {
		facet->setTopLeftVertex(wVertices[0]);
		facet->setBottomLeftVertex(wVertices[1]);
	}
	else {
		facet->setTopLeftVertex(wVertices[1]);
		facet->setBottomLeftVertex(wVertices[0]);
	}

	if (wVertices[2].y < wVertices[3].y) {
		facet->setTopRightVertex(wVertices[2]);
		facet->setBottomRightVertex(wVertices[3]);
	}
	else {
		facet->setTopRightVertex(wVertices[3]);
		facet->setBottomRightVertex(wVertices[2]);
	}

	return facet;
}

CircularFacet* FacetFactory::createCircularFacet(CvPoint center, float radius) {

	CircularFacet* facet = new CircularFacet();
	facet->setCenterPosition(center);
	facet->setRadius(radius);

	return facet;
}

}}}};