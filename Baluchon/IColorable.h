#pragma once

#include <cv.h>

namespace baluchon { namespace core { namespace datas {

class IColorable
{
public:
	virtual ~IColorable(void) {}
	
	virtual void setColor(int r, int g, int b, int a = 0.0) {
		mColor = cvScalar(r, g, b, a);
	}

	virtual void setColor(CvScalar color) {
		mColor = color;
	}

	virtual CvScalar getColor(void) {
		return mColor;
	}

protected:
	CvScalar mColor;
};

}}};