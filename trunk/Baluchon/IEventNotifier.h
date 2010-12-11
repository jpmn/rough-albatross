#pragma once

#include "IEventHandler.h"
#include <vector>

using namespace std;

namespace baluchon { namespace core { namespace events {

class IEventNotifier
{
public:
    ~IEventNotifier(void) {};

    virtual void addEventHandler(IEventHandler* eventHandler)
    {
        mEventHandlers.push_back(eventHandler);
    }

    virtual void notifyEventHandlers(IEvent* e)
    {
        for(unsigned int i = 0; i < mEventHandlers.size(); i++)
        {
            mEventHandlers[i]->handle(e);
        }
    }

private:
    vector<IEventHandler*> mEventHandlers;
};

}}};