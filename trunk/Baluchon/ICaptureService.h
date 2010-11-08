#pragma once

#include <highgui.h>

#include "IService.h"

namespace baluchon { namespace core { namespace services { 

DeclareBasedInterface(ICaptureService, IService)
	virtual void setCapture(CvCapture* capture) = 0;
	virtual IplImage* getImage(void) = 0;
EndInterface

}}};
