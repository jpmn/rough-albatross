#pragma once

#include <cv.h>

namespace baluchon { namespace core { namespace datas {

class IPositionable
{
public:
	virtual ~IPositionable(void) {}

	virtual void setPosition(int x, int y) {
		mPosition = cvPoint(x, y);
	}

	virtual void setPosition(CvPoint position) {
		mPosition = position;	
	}

	virtual CvPoint getPosition(void) {
		return mPosition;
	}

protected:
	CvPoint mPosition;
};

}}};