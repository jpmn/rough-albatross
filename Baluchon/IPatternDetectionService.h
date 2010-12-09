#pragma once

#include "IService.h"
#include "IDetectedPattern.h"

namespace baluchon { namespace core { namespace services { namespace patterndetection { 

class IPatternDetectionService : public IService
{
public:
    virtual ~IPatternDetectionService(void) {};

    virtual void addPattern(IPattern* pattern) = 0;
    virtual bool addPattern(char patternName[]) = 0;
    virtual vector<IDetectedPattern*> getPatterns() = 0;
};

}}}};