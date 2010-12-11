#pragma once

#include "IEvent.h"

namespace baluchon { namespace core { namespace events {

class IEventHandler
{
public:
    virtual ~IEventHandler(void) {};

    virtual void handle(IEvent* e) = 0;
};

}}};