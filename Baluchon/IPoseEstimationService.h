#pragma once

#include "IService.h"

namespace baluchon { namespace core { namespace services { namespace poseestimation { 

class IPoseEstimationService : public IService
{
public:
    virtual ~IPoseEstimationService(void) {};
};

}}}};