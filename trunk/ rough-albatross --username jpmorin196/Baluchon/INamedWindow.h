#pragma once

#include <cv.h>
#include "CppInterface.h"

namespace Baluchon { namespace Core { namespace Components {

DeclareInterface(INamedWindow)
	virtual void init(void) = 0;
	virtual void show(void) = 0;

	virtual void setName(const char* name) = 0;
	virtual void setFlag(int flag) = 0;
	virtual void setImage(const IplImage* image) = 0;
EndInterface

}}};
