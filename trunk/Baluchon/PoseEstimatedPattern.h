#pragma once
#include "iposeestimatedpattern.h"
#include "idetectedpattern.h"

namespace baluchon { namespace core { namespace services { namespace poseestimation { 

class PoseEstimatedPattern :
    public IPoseEstimatedPattern
{
public:
    PoseEstimatedPattern(IDetectedPattern *mPattern);
    ~PoseEstimatedPattern(void);

    int getWidth();
    int getHeight();
    int getPointCount();
    CvPoint2D32f getSourcePointAt(int pos, int orientation = 0);

    vector<vector<CvPoint2D32f>>* getImagePoints();
    vector<vector<CvPoint2D32f>>* getImageFramePoints();
    vector<int>* getImageOrientations();

    vector<CvMat*>* getRotationMatrices();
    vector<CvMat*>* getTranslationMatrices();
    bool decorates(IPattern *pattern);

private:

    IDetectedPattern *mPattern;
    vector<CvMat*>* mRotationMatrices;
    vector<CvMat*>* mTranslationMatrices;

};

}}}};