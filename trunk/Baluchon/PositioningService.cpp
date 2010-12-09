#include "PositioningService.h"
#include "PoseEstimationService.h"
#include "CameraCaptureService.h"
#include "IServiceLayer.h"

namespace baluchon { namespace core { namespace services { namespace positioning { 

PositioningService::PositioningService(char* intrinsicPath, char* distortionPath)
{
    mIntrinsicPath = intrinsicPath;
    mDistortionPath = distortionPath;
}


PositioningService::~PositioningService(void)
{
}

void PositioningService::init(void) {
    mPoseEstimationService = new PoseEstimationService(0,0);
    mPoseEstimationService = (IPoseEstimationService*) mServiceLayer->findService(mPoseEstimationService);

    mCaptureService= new CameraCaptureService();
    mCaptureService = (ICaptureService*) mServiceLayer->findService(mCaptureService);

    CvMat* intrinsic = (CvMat*)cvLoad(mIntrinsicPath);
    CvMat* distortion = (CvMat*)cvLoad(mDistortionPath);

    mVisitor = new PositioningVisitor(intrinsic, distortion);


    unsigned int cpt;
    bool found;
    map<IPattern*, IGraphic*>::const_iterator iter;
    for (iter=mInitialSceneGraphs.begin(); iter != mInitialSceneGraphs.end(); ++iter) {
        cpt = 0;
        found = false;

        while(!found && cpt < mPoseEstimationService->getPatterns().size())
        {
            found = mPoseEstimationService->getPatterns()[cpt] == iter->first || mPoseEstimationService->getPatterns()[cpt]->decorates(iter->first);
            if(found)
            {
                mSceneGraphs[mPoseEstimationService->getPatterns()[cpt]] = iter->second;
            }
            else
            {
                cpt++;
            }
        }
    }
}

void PositioningService::initDone(void) {

}

void PositioningService::execute(void) {
    mVisitor->setImage(mCaptureService->getImage());

    
    map<IPoseEstimatedPattern*, IGraphic*>::const_iterator iter;
    for (iter=mSceneGraphs.begin(); iter != mSceneGraphs.end(); ++iter) {
        for(unsigned int i = 0; i < iter->first->getImagePoints()->size(); i++)
        {
            mVisitor->setRotationMat((*(iter->first->getRotationMatrices()))[i]);
            mVisitor->setTranslationMat((*(iter->first->getTranslationMatrices()))[i]);

            iter->second->reset();
            iter->second->accept(mVisitor);
        }
    }
}

void PositioningService::reset(void) {

}

void PositioningService::dispose(void) {
}

void PositioningService::addSceneGraph(IPattern *pattern, IGraphic *root)
{
    mInitialSceneGraphs[pattern] = root;
}

}}}};