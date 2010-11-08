#pragma once

#include "MacroInterface.h"

namespace baluchon { namespace core { namespace services {

DeclareInterface(IService)
	virtual void init(void) = 0;
	virtual void initDone(void) = 0;
	virtual void execute(void) = 0;
	virtual void reset(void) = 0;
	virtual void dispose(void) = 0;
EndInterface

}}};