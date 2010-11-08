#pragma once

#include "MacroInterface.h"
#include "IService.h"

namespace Baluchon { namespace Core { namespace Services {

DeclareInterface(IServiceLayer)
	virtual void SetLowerLayer(IServiceLayer* serviceLayer) = 0;
	virtual void AddService(IService* service) = 0;
	virtual IService* FindServiceInLowerLayer(IService* service) = 0;
EndInterface

}}};