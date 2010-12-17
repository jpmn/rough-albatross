#include "CircularFacet.h"

namespace baluchon { namespace core { namespace services { namespace objectdetection {

CircularFacet::CircularFacet(void) {

}

CircularFacet::~CircularFacet(void) {

}

CvPoint CircularFacet::getCenterPosition(void) {
	return mCenter;
}

void CircularFacet::setCenterPosition(CvPoint center) {
	mCenter = center;
}

void CircularFacet::setRadius(float radius) {
	mRadius = radius;
}

float CircularFacet::getRadius(void) {
	return mRadius;
}

}}}};