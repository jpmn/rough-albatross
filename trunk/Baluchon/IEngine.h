#pragma once

#include "IServiceLayer.h"
#include "MacroInterface.h"

using namespace Baluchon::Core::Services;

namespace Baluchon { namespace Core { namespace Engine {

DeclareInterface(IEngine)
	virtual void Init(void) = 0;
	virtual void Run(void) = 0;
	virtual void Reset(void) = 0;
	virtual void Dispose(void) = 0;

	virtual void SetExitKey(char exitKey) = 0;
	virtual void AddServiceLayer(IServiceLayer* serviceLayer) = 0;
EndInterface

}}};