#pragma once

#include "IDetector.h"
#include "FacetFactory.h"
#include "RectangularFacet.h"

namespace baluchon { namespace core { namespace services { namespace objectdetection {

class RectangleDetector : public IDetector
{
public:
	RectangleDetector(void);
	virtual ~RectangleDetector(void);

	vector<IDetectable*> find(IplImage* img, IplImage* src);

private:
	FacetFactory* mFacetFactory;
};

}}}};