#pragma once

#include <cv.h>

#include "CppInterface.h"

namespace Baluchon { namespace Core { namespace Services {

DeclareInterface(IService)
	virtual void execute(IplImage* img) = 0;
	virtual void initialize(void) = 0;
	virtual void initializeDone(void) = 0;
	virtual void reset(void) = 0;
EndInterface

}}};