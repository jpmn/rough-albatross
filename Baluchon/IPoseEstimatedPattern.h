#pragma once
#include "idetectedpattern.h"

using namespace baluchon::core::services::patterndetection;

namespace baluchon { namespace core { namespace services { namespace poseestimation { 

class IPoseEstimatedPattern :
    public IDetectedPattern
{
public:
    ~IPoseEstimatedPattern(void) {};

    virtual vector<CvMat*>* getRotationMatrices() = 0;
    virtual vector<CvMat*>* getTranslationMatrices() = 0;
};

}}}};