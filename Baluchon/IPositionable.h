#pragma once

#include <cv.h>

namespace baluchon { namespace core { namespace datas {

class IPositionable
{
public:
	virtual ~IPositionable(void) {}

	virtual void setPosition(int x, int y) = 0;
	virtual void setPosition(CvPoint p) = 0;
	virtual CvPoint getPosition(void) = 0;
};

}}};