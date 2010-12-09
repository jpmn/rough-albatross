#include "PoseEstimatedPattern.h"

namespace baluchon { namespace core { namespace services { namespace poseestimation { 

PoseEstimatedPattern::PoseEstimatedPattern(IDetectedPattern *pattern)
{
    mPattern = pattern;

    mRotationMatrices = new vector<CvMat*>();
    mTranslationMatrices = new vector<CvMat*>();
}


PoseEstimatedPattern::~PoseEstimatedPattern(void)
{
}

int PoseEstimatedPattern::getWidth()
{
    return mPattern->getWidth();
}

int PoseEstimatedPattern::getPointCount()
{
    return mPattern->getPointCount();
}

int PoseEstimatedPattern::getHeight()
{
    return mPattern->getHeight();
}

CvPoint2D32f PoseEstimatedPattern::getSourcePointAt(int pos, int orientation)
{
    return mPattern->getSourcePointAt(pos, orientation);
}

vector<vector<CvPoint2D32f>>* PoseEstimatedPattern::getImagePoints()
{
    return mPattern->getImagePoints();
}

vector<vector<CvPoint2D32f>>* PoseEstimatedPattern::getImageFramePoints()
{
    return mPattern->getImageFramePoints();
}

vector<CvMat*>* PoseEstimatedPattern::getRotationMatrices()
{
    return mRotationMatrices;
}

vector<CvMat*>* PoseEstimatedPattern::getTranslationMatrices()
{
    return mTranslationMatrices;
}

bool PoseEstimatedPattern::decorates(IPattern *pattern)
{
    if(mPattern == pattern)
    {
        return true;
    }
    else
    {
        return mPattern->decorates(pattern);
    }
}

}}}};
