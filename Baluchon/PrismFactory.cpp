#include "PrismFactory.h"

namespace baluchon { namespace core { namespace services { namespace objectdetection {

PrismFactory::PrismFactory(void) {

}

PrismFactory::~PrismFactory(void) {

}

BoxPrism* PrismFactory::createBoxPrism(RectangularFacet* facet1, RectangularFacet* facet2, RectangularFacet* facet3) {
	
	vector<RectangularFacet*> mFacets;
	mFacets.push_back(facet1);
	mFacets.push_back(facet2);
	mFacets.push_back(facet3);

	std::sort(mFacets.begin(), mFacets.end(), IPrism::sortByCenterPositionY);
	
	BoxPrism* prism = new BoxPrism();
	prism->setTopFacet(mFacets[0]);

	if (mFacets[1]->getCenterPosition().x < mFacets[2]->getCenterPosition().x) {
		prism->setFrontFacet(mFacets[1]);
		prism->setSideFacet(mFacets[2]);
	}
	else {
		prism->setFrontFacet(mFacets[2]);
		prism->setSideFacet(mFacets[1]);
	}

	return prism;
}

}}}};