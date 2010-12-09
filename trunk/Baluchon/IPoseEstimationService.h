#pragma once

#include "IService.h"
#include "IPoseEstimatedPattern.h"

namespace baluchon { namespace core { namespace services { namespace poseestimation { 

class IPoseEstimationService : public IService
{
public:
    virtual ~IPoseEstimationService(void) {};

    virtual vector<IPoseEstimatedPattern*> getPatterns() = 0;
};

}}}};