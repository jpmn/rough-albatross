#pragma once
#include "ipattern.h"

namespace baluchon { namespace core { namespace services { namespace patterndetection { 

class IDetectedPattern :
    public IPattern
{
public:
    ~IDetectedPattern(void) {};

    virtual vector<vector<CvPoint2D32f>>* getImagePoints() = 0;
    virtual vector<vector<CvPoint2D32f>>* getImageFramePoints() = 0;
    virtual bool decorates(IPattern *pattern) = 0;
};

}}}};