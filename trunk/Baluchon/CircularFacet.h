#pragma once

#include "IFacet.h"
#include "IDetectable.h"

using namespace baluchon::core::datas;

namespace baluchon { namespace core { namespace services { namespace objectdetection {

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