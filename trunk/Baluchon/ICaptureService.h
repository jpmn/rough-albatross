#pragma once

#include <highgui.h>

#include "IService.h"

namespace baluchon { namespace core { namespace services { namespace capture { 

class ICaptureService : public IService
{
public:
	virtual ~ICaptureService() {}

	virtual void setCapture(CvCapture* capture) = 0;
	virtual IplImage* getImage(void) = 0;
	virtual CvSize getSize(void) = 0;
};

}}}};
