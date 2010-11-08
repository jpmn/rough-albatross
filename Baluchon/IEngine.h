#pragma once

#include "IServiceLayer.h"
#include "MacroInterface.h"

using namespace baluchon::core::services;

namespace baluchon { namespace core { namespace engine {

class IEngine
{
	virtual ~IEngine() {}

	virtual void init(void) = 0;
	virtual void run(void) = 0;
	virtual void reset(void) = 0;
	virtual void dispose(void) = 0;

	virtual void setExitKey(char exitKey) = 0;
	virtual void addServiceLayer(IServiceLayer* serviceLayer) = 0;
}

}}};