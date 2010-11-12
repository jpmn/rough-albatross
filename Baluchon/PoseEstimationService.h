#pragma once
#include "iposeestimationservice.h"
#include "IPatternDetectionService.h"

using namespace baluchon::core::services::patterndetection;

namespace baluchon { namespace core { namespace services { namespace poseestimation { 

class PoseEstimationService :
    public IPoseEstimationService
{
public:
    PoseEstimationService(void);
    ~PoseEstimationService(void);

    virtual void init(void);
	virtual void initDone(void);
	virtual void execute(void);
	virtual void reset(void);
	virtual void dispose(void);

private:
    IPatternDetectionService* mPatternDetectionService;
};

}}}};