#pragma once
#include "iservice.h"
#include "iaugmentedcomponent.h"

namespace baluchon { namespace core { namespace services { namespace augmentedinterface {

class IAugmentedInterfaceService :
    public IService
{
public:
    virtual ~IAugmentedInterfaceService(void) {};

    virtual void addAugmentedComponent(IAugmentedComponent *component) = 0;
    virtual void removeAugmentedComponent(IAugmentedComponent *component) = 0;
};

}}}};