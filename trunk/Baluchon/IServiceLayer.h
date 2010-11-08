#pragma once

#include <typeinfo>
#include <vector>

#include "IService.h"

namespace baluchon { namespace core { namespace services {

class IServiceLayer 
{
public:
	virtual ~IServiceLayer() {}

	virtual void setLowerLayer(IServiceLayer* serviceLayer) = 0;
	virtual IServiceLayer* getLowerLayer(void) = 0;
	virtual void addService(IService* service) = 0;
	virtual IService* findService(IService* service) = 0;
	virtual vector<IService*> getServices(void) = 0;
};

}}};
