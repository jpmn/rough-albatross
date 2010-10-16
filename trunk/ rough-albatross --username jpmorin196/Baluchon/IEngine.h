#pragma once

#include "CppInterface.h"
#include "INamedWindow.h"
#include "IService.h"

using namespace Baluchon::Core::Components;
using namespace Baluchon::Core::Services;

namespace Baluchon { namespace Core {

DeclareInterface(IEngine)
	virtual void init(void) = 0;
	virtual void cycle(void) = 0;
	virtual void dispose(void) = 0;
	virtual void registerService(IService* s) = 0;

	virtual void setNamedWindow(INamedWindow *nw) = 0;
	virtual void setExitKey(char key) = 0;
	virtual void setCycleDuration(int ms) = 0;
EndInterface

}};
