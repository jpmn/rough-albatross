#pragma once
#include "ipositioningservice.h"
#include "IPoseEstimationService.h"
#include "IPoseEstimatedPattern.h"
#include "ICaptureService.h"
#include "PositioningVisitor.h"
#include <vector>
#include <map>

using namespace baluchon::core::services::poseestimation;
using namespace baluchon::core::services::capture;

namespace baluchon { namespace core { namespace services { namespace positioning { 

class PositioningService :
    public IPositioningService
{
public:
    PositioningService(char* intrinsicPath, char* distortionPath);
    ~PositioningService(void);

    void addSceneGraph(IPattern *pattern, IGraphic *root);

    virtual void init(void);
	virtual void initDone(void);
	virtual void execute(void);
	virtual void reset(void);
	virtual void dispose(void);

private:
    IPoseEstimationService* mPoseEstimationService;
    ICaptureService* mCaptureService;
    PositioningVisitor* mVisitor;
    char* mIntrinsicPath;
    char* mDistortionPath;
    map<IPattern*, IGraphic*> mInitialSceneGraphs;
    map<IPoseEstimatedPattern*, IGraphic*> mSceneGraphs;
};

}}}};
