#pragma once

#include "IPrism.h"
#include "IDetectable.h"
#include "RectangularFacet.h"

using namespace baluchon::core::datas;

namespace baluchon { namespace core { namespace services { namespace objectdetection {

class BoxPrism : public IPrism, public IDetectable
{
public:
	BoxPrism(void);
	virtual ~BoxPrism(void);

	vector<RectangularFacet*> getFacets(void);
	
	void setFrontFacet(RectangularFacet*);
	void setSideFacet(RectangularFacet*);
	void setTopFacet(RectangularFacet*);

	RectangularFacet* getFrontFacet(void);
	RectangularFacet* getSideFacet(void);
	RectangularFacet* getTopFacet(void);

private:
	//   Top		Top
	//  /¯¯/|	   |\¯¯\
	//  |¯¯|/ Side \|¯¯|
	//  Front	   Front
	RectangularFacet* mFrontFacet;
	RectangularFacet* mSideFacet;
	RectangularFacet* mTopFacet;
};

}}}};