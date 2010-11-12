#pragma once

#include <cv.h>

namespace baluchon { namespace core { namespace datas {

class ISizeable 
{
public:
	virtual ~ISizeable(void) {}

	virtual void setSize(int width, int height) {
		mSize = cvSize(width, height);
	}

	virtual void setSize(CvSize size) {
		mSize = size;
	}

	virtual CvSize getSize() {
		return mSize;	
	}

protected:
	CvSize mSize;
};

}}};