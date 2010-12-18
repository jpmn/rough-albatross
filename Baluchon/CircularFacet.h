#pragma once

#include "IFacet.h"
#include "IDetectable.h"

namespace baluchon { namespace core { namespace datas { namespace detection {

class CircularFacet : public IFacet, public IDetectable
{
public:
	CircularFacet(void);
	virtual ~CircularFacet(void);

	CvPoint getCenterPosition(void);
	
	void setCenterPosition(CvPoint center);
	void setRadius(float radius);

	float getRadius(void);

private:
	CvPoint mCenter;
	float mRadius;
};

}}}};