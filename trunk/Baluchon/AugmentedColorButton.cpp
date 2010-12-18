#include "AugmentedColorButton.h"
#include "ColorButtonEvent.h"
#include "ColoredMarker.h"

using namespace baluchon::core::datas::detection;

namespace baluchon { namespace core { namespace services { namespace augmentedinterface {

AugmentedColorButton::AugmentedColorButton(IColorDetectionService* colorDetectionService, CvPoint pos, int width, int height)
{
    mColorDetectionService = colorDetectionService;
    mPos = pos;
    mWidth = width;
    mHeight = height;
    mHover = false;
    mCpt = 0;
}


AugmentedColorButton::~AugmentedColorButton(void)
{
}

void AugmentedColorButton::execute()
{
	vector<IDetectable*> wListDetectables = mColorDetectionService->getDetectables();

    bool found = false;
    unsigned int cpt = 0;
    if(mHover)
    {
        mCpt++;

        if(mCpt > 10)
        {
            mHover = false;
            mCpt = 0;
        }
    }

    while(!found && cpt < wListDetectables.size())
    {
		ColoredMarker* wMarker = static_cast<ColoredMarker*>(wListDetectables[cpt]);
		CvPoint wMarkerPosition = wMarker->getPosition();

        if(wMarkerPosition.x >= mPos.x && wMarkerPosition.x <= mPos.x + mWidth &&
            wMarkerPosition.y >= mPos.y && wMarkerPosition.y <= mPos.y + mHeight)
        {
            mHover = true;
            found = true;
        }
        
		cpt++;
    }

    if(found)
    {
        ColorButtonEvent* evt = new ColorButtonEvent();
        evt->setEventNotifier(this);
        notifyEventHandlers(evt);
    }
}

void AugmentedColorButton::draw(IplImage* img)
{
    cvDrawRect(img, cvPoint(mPos.x, mPos.y), cvPoint(mPos.x + mWidth, mPos.y + mHeight), CV_RGB((mHover ? 0 : 255), (mHover ? 255 : 0), 0), 4);
}

}}}};