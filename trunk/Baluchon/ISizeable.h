#pragma once

#include <cv.h>

namespace baluchon { namespace core { namespace datas {

class ISizeable 
{
public:
	virtual ~ISizeable(void) {}

	virtual void setSize(int w, int h) = 0;
	virtual void setSize(CvSize s) = 0;
	virtual CvSize getSize() = 0;
};

}}};