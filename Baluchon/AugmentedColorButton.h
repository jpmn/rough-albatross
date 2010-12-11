#pragma once
#include "iaugmentedcomponent.h"
#include "icolordetectionservice.h"

using namespace baluchon::core::services::colordetection;

namespace baluchon { namespace core { namespace services { namespace augmentedinterface {

class AugmentedColorButton :
    public IAugmentedComponent
{
public:
    AugmentedColorButton(IColorDetectionService* colorDetectionService, CvPoint pos, int width, int height);
    ~AugmentedColorButton(void);

    void execute();
    void draw(IplImage* img);

private:
    IColorDetectionService* mColorDetectionService;
    bool mHover;
    int mCpt;
};

}}}};