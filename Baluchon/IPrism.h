#pragma once

#include "IFacet.h"

namespace baluchon { namespace core { namespace services { namespace objectdetection {

class IPrism
{
public:
	virtual ~IPrism(void) {}

	static bool sortByCenterPositionX(IFacet* f1, IFacet* f2) {
		return f1->getCenterPosition().x < f2->getCenterPosition().x;
	}

	static bool sortByCenterPositionY(IFacet* f1, IFacet* f2) {
		return f1->getCenterPosition().y < f2->getCenterPosition().y;
	}
};

}}}};