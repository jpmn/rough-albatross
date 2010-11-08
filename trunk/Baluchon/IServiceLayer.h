#pragma once

#include "IService.h"

namespace baluchon { namespace core { namespace services {

class IServiceLayer
{
public:
    virtual ~IServiceLayer(){}
	virtual void setLowerLayer(IServiceLayer* serviceLayer) = 0;
	virtual void addService(IService* service) = 0;
	virtual IService* findServiceInLowerLayer(IService* service) = 0;
};

}}};