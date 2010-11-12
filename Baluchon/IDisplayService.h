#pragma once

#include <highgui.h>

#include "IService.h"

namespace baluchon { namespace core { namespace services { namespace display { 

class IDisplayService : public IService
{
public:
	virtual ~IDisplayService() {}

	virtual void setWindowName(char* name) = 0;
	virtual IplImage* getImage() = 0;
};

}}}};