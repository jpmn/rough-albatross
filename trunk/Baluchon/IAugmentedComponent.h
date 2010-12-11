#pragma once
#include "ieventnotifier.h"
#include "cv.h"

using namespace baluchon::core::events;

namespace baluchon { namespace core { namespace services { namespace augmentedinterface {

class IAugmentedComponent :
    public IEventNotifier
{
public:
    ~IAugmentedComponent(void) {};

    // called at every frame. Checks for events and notifies handlers. Empty = default.
    virtual void execute() {};

    // called at every frame, after execute
    virtual void draw(IplImage* img) = 0;

    void setPosition(CvPoint pos)
    {
        mPos = pos;
    }

    CvPoint getPosition()
    {
        return mPos;
    }

    void setSize(int width, int height)
    {
        mWidth = width;
        mHeight = height;
    }

    int getWidth()
    {
        return mWidth;
    }

    int getHeight()
    {
        return mHeight;
    }

protected:
    CvPoint mPos;
    int mWidth;
    int mHeight;
};

}}}};