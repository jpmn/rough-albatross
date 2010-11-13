#pragma once

#include <cv.h>

namespace baluchon { namespace core { namespace datas {

class IColorable
{
public:
	virtual ~IColorable(void) {}
	
	virtual void setColor(int b, int g, int r) {
		mColor = cvScalar(b, g, r);
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