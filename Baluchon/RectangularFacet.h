#pragma once

#include "IFacet.h"
#include "IDetectable.h"

using namespace baluchon::core::datas;

namespace baluchon { namespace core { namespace services { namespace objectdetection {

class RectangularFacet : public IFacet, public IDetectable
{
public:
	RectangularFacet(void);
	virtual ~RectangularFacet(void);
	
	CvPoint getCenterPosition(void);
	
	void setTopLeftVertex(CvPoint vertex);
	void setTopRightVertex(CvPoint vertex);
	void setBottomLeftVertex(CvPoint vertex);
	void setBottomRightVertex(CvPoint vertex);

	CvPoint getTopLeftVertex(void);
	CvPoint getTopRightVertex(void);
	CvPoint getBottomLeftVertex(void);
	CvPoint getBottomRightVertex(void);

private:
	CvPoint mTopLeftVertex;
	CvPoint mTopRightVertex;
	CvPoint mBottomLeftVertex;
	CvPoint mBottomRightVertex;
};

}}}};