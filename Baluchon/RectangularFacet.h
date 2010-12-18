#pragma once

#include "IFacet.h"
#include "IDetectable.h"

namespace baluchon { namespace core { namespace datas { namespace detection {

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