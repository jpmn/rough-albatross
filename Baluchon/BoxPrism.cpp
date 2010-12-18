#include "BoxPrism.h"

namespace baluchon { namespace core { namespace datas { namespace detection {

BoxPrism::BoxPrism(void) {

}

BoxPrism::~BoxPrism(void) {

}

void BoxPrism::setFrontFacet(RectangularFacet* facet) {
	mFrontFacet = facet;
}

void BoxPrism::setSideFacet(RectangularFacet* facet) {
	mSideFacet = facet;
}

void BoxPrism::setTopFacet(RectangularFacet* facet) {
	mTopFacet = facet;
}

RectangularFacet* BoxPrism::getFrontFacet(void) {
	return mFrontFacet;
}

RectangularFacet* BoxPrism::getSideFacet(void) {
	return mSideFacet;
}

RectangularFacet* BoxPrism::getTopFacet(void) {
	return mTopFacet;
}

}}}};