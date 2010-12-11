#pragma once
#include "ieventhandler.h"
#include "icaptureservice.h"

using namespace baluchon::core::events;
using namespace baluchon::core::services::capture;

class TestEventHandler :
    public IEventHandler
{
public:
    TestEventHandler(ICaptureService* capture);
    ~TestEventHandler(void);

    void handle(IEvent* e);

private:
    ICaptureService* mCaptureService;
};

