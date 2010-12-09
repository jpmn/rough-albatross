#pragma once
#include "iposeestimationservice.h"
#include "IPatternDetectionService.h"
#include "ICaptureService.h"
#include "IPoseEstimatedPattern.h"
#include <vector>

using namespace baluchon::core::services::patterndetection;
using namespace baluchon::core::services::capture;

namespace baluchon { namespace core { namespace services { namespace poseestimation { 

class PoseEstimationService :
    public IPoseEstimationService
{
public:
    PoseEstimationService(char* intrisicPath, char* distortionPath);
    ~PoseEstimationService(void);

    virtual void init(void);
	virtual void initDone(void);
	virtual void execute(void);
	virtual void reset(void);
	virtual void dispose(void);
    vector<IPoseEstimatedPattern*> getPatterns();

private:
    vector<IPoseEstimatedPattern*> mPatterns;
    IPatternDetectionService* mPatternDetectionService;
    ICaptureService* mCaptureService;
    CvMat* mIntrinsic;
	CvMat* mDistortion;
    char* mIntrinsicPath;
    char* mDistortionPath;
};

}}}};