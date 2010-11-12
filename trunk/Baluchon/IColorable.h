#pragma once

#include <cv.h>

namespace baluchon { namespace core { namespace datas {

class IColorable
{
public:
	virtual ~IColorable(void) {}
	
	virtual void setColor(int rgba);
	virtual void setColor(int r, int g, int b, int a = 0) = 0;
	virtual void setColor(CvScalar s) = 0;
	virtual CvScalar getColor(void) = 0; 
};

}}};