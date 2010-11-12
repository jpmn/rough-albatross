#pragma once

#include <cv.h>

#include "IPositionable.h"
#include "ISizeable.h"

using namespace baluchon::core::datas;

namespace baluchon { namespace core { namespace services { namespace colordetection {

class IBlob : public IPositionable, ISizeable
{
public:
	virtual ~IBlob(void) {}

	virtual void setContour(CvSeq* contour) {
		mContour = contour;
	}

	virtual CvSeq* getContour(void) {
		return mContour;	
	}

protected:
	CvSeq* mContour;
};

}}}};