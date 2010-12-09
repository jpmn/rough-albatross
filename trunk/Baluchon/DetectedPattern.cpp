#include "DetectedPattern.h"

namespace baluchon { namespace core { namespace services { namespace patterndetection { 

DetectedPattern::DetectedPattern(IPattern *pattern)
{
    mPattern = pattern;

    mImgPoints = new vector<vector<CvPoint2D32f>>();
    mFramePoints = new vector<vector<CvPoint2D32f>>();
}


DetectedPattern::~DetectedPattern(void)
{
}

int DetectedPattern::getWidth()
{
    return mPattern->getWidth();
}

int DetectedPattern::getPointCount()
{
    return mPattern->getPointCount();
}

int DetectedPattern::getHeight()
{
    return mPattern->getHeight();
}

CvPoint2D32f DetectedPattern::getSourcePointAt(int pos, int orientation)
{
    return mPattern->getSourcePointAt(pos, orientation);
}

vector<vector<CvPoint2D32f>>* DetectedPattern::getImagePoints()
{
    return mImgPoints;
}

vector<vector<CvPoint2D32f>>* DetectedPattern::getImageFramePoints()
{
    return mFramePoints;
}

bool DetectedPattern::decorates(IPattern *pattern)
{
    if(mPattern == pattern)
    {
        return true;
    }
    else
    {
        return false;
    }
}

}}}};
