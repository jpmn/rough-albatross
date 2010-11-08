#pragma once

#include "MacroInterface.h"

namespace Baluchon { namespace Core { namespace Services {

DeclareInterface(IService)
	virtual void Init(void) = 0;
	virtual void InitDone(void) = 0;
	virtual void Execute(void) = 0;
	virtual void Reset(void) = 0;
	virtual void Dispose(void) = 0;
EndInterface

}}};