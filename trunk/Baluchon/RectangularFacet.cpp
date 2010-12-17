#include "RectangularFacet.h"

#include "MathUtility.h"

using namespace baluchon::utilities;

namespace baluchon { namespace core { namespace services { namespace objectdetection {

RectangularFacet::RectangularFacet(void) {

}

RectangularFacet::~RectangularFacet(void) {

}

CvPoint RectangularFacet::getCenterPosition(void) {
	return MathUtility::middle(this->getTopLeftVertex(), this->getBottomRightVertex());
}

void RectangularFacet::setTopLeftVertex(CvPoint vertex) {
	mTopLeftVertex = vertex;
}

void RectangularFacet::setTopRightVertex(CvPoint vertex) {
	mTopRightVertex = vertex;
}

void RectangularFacet::setBottomLeftVertex(CvPoint vertex) {
	mBottomLeftVertex = vertex;
}

void RectangularFacet::setBottomRightVertex(CvPoint vertex) {
	mBottomRightVertex = vertex;
}

CvPoint RectangularFacet::getTopLeftVertex(void) {
	return mTopLeftVertex;
}

CvPoint RectangularFacet::getTopRightVertex(void) {
	return mTopRightVertex;
}

CvPoint RectangularFacet::getBottomLeftVertex(void) {
	return mBottomLeftVertex;
}

CvPoint RectangularFacet::getBottomRightVertex(void) {
	return mBottomRightVertex;
}

}}}};