#pragma once

#include "MacroInterface.h"
#include "IService.h"

namespace baluchon { namespace core { namespace services {

DeclareInterface(IServiceLayer)
	virtual void setLowerLayer(IServiceLayer* serviceLayer) = 0;
	virtual void addService(IService* service) = 0;
	virtual IService* findServiceInLowerLayer(IService* service) = 0;
EndInterface

}}};