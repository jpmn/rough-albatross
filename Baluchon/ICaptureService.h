#pragma once

#include <highgui.h>

#include "IService.h"

namespace Baluchon { namespace Core { namespace Services { 

DeclareBasedInterface(ICaptureService, IService)
	virtual void SetCapture(CvCapture* capture) = 0;
	virtual IplImage* GetImage(void) = 0;
EndInterface

}}};
