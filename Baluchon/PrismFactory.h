#pragma once

#include "BoxPrism.h"

using namespace baluchon::core::datas::detection;

namespace baluchon { namespace core { namespace services { namespace objectdetection {

class PrismFactory
{
public:
	PrismFactory(void);
	~PrismFactory(void);

	BoxPrism* createBoxPrism(RectangularFacet* facet1, RectangularFacet* facet2, RectangularFacet* facet3);
};

}}}};