#pragma once

namespace baluchon { namespace core { namespace events {

class IEventNotifier;

class IEvent
{
public:
    virtual ~IEvent() {};

    virtual int getState()
    {
        return mState;
    }

    virtual void setEventNotifier(IEventNotifier* eventNotifier)
    {
        mEventNotifier = eventNotifier;
    }

    virtual IEventNotifier* getEventNotifier()
    {
        return mEventNotifier;
    }

protected:
    int mState;
    IEventNotifier* mEventNotifier;
};

}}};
