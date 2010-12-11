#pragma once
#include "ievent.h"

using namespace baluchon::core::events;

namespace baluchon { namespace core { namespace services { namespace augmentedinterface {

class ColorButtonEvent :
    public IEvent
{
public:
    ColorButtonEvent(void);
    ~ColorButtonEvent(void);
};

}}}};