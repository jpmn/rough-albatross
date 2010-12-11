#include "AugmentedColorButton.h"
#include "ColorButtonEvent.h"

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
    vector<IMarker*> markers = mColorDetectionService->getMarkers();
    bool found = false;
    unsigned int cpt = 0;
    unsigned int cpt2 = 0;
    if(mHover)
    {
        mCpt++;

        if(mCpt > 10)
        {
            mHover = false;
            mCpt = 0;
        }
    }

    while(!found && cpt < markers.size())
    {
        while(!found && cpt2 < markers[cpt]->getBlobs().size())
        {
            if(markers[cpt]->getBlobs()[cpt2]->getPosition().x >= mPos.x &&
                markers[cpt]->getBlobs()[cpt2]->getPosition().x <= mPos.x + mWidth &&
                markers[cpt]->getBlobs()[cpt2]->getPosition().y >= mPos.y &&
                markers[cpt]->getBlobs()[cpt2]->getPosition().y <= mPos.y + mHeight)
            {
                mHover = true;
                found = true;
            }
            else
            {
                cpt2++;
            }
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