#pragma once

#include <highgui.h>

#include "IService.h"

namespace baluchon { namespace core { namespace services { 

class ICaptureService : IService
{
public:
    virtual ~ICaptureService() {}

    virtual void setCapture(CvCapture* capture) = 0;
	virtual IplImage* getImage(void) = 0;
};

}}};
