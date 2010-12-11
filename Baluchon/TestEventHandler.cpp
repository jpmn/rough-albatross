#include "TestEventHandler.h"


TestEventHandler::TestEventHandler(ICaptureService* capture)
{
    mCaptureService = capture;
}


TestEventHandler::~TestEventHandler(void)
{
}

void TestEventHandler::handle(IEvent* e)
{
    if(e->getState() == 1)
    {
        CvFont font;
        cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 1.0, 1.0, 0, 2, CV_AA);
        cvPutText(mCaptureService->getImage(), "Button event received", cvPoint(10, 475), &font, cvScalar(255, 255, 255, 0));
    }
}
