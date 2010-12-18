#pragma once

#include "IMarker.h"
#include "IDetectable.h"
#include "IColorable.h"
#include "IPositionable.h"

using namespace baluchon::core::datas;

namespace baluchon { namespace core { namespace datas { namespace detection {

class ColoredMarker : public IMarker, public IColorable, public IPositionable, public IDetectable
{
public:
	ColoredMarker(void);
	virtual ~ColoredMarker(void);

	void setContours(CvSeq* contours);
	CvSeq* getContours(void);

	void setTolerance(int tolerance);
	int getTolerance(void);

private:
	CvMemStorage* mStorage;
	CvSeq* mContours;
	int mTolerance;
};

}}}};