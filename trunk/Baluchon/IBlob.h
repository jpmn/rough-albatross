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

	virtual void setContours(CvSeq* contours) = 0;
	virtual CvSeq* getContours(void) = 0;
};

}}}};