#pragma once
#include "iservice.h"
#include "ipattern.h"
#include "igraphic.h"

using namespace baluchon::core::services::patterndetection;

namespace baluchon { namespace core { namespace services { namespace positioning { 

class IPositioningService :
    public IService
{
public:
    virtual ~IPositioningService(void) {};

    virtual void addSceneGraph(IPattern *pattern, IGraphic *root) = 0;
};

}}}};
