#pragma once
#include "idetectedpattern.h"

namespace baluchon { namespace core { namespace services { namespace patterndetection { 

class DetectedPattern :
    public IDetectedPattern
{
public:
    DetectedPattern(IPattern *mPattern);
    ~DetectedPattern(void);

    int getWidth();
    int getHeight();
    int getPointCount();
    CvPoint2D32f getSourcePointAt(int pos, int orientation = 0);

    vector<vector<CvPoint2D32f>>* getImagePoints();
    vector<vector<CvPoint2D32f>>* getImageFramePoints();
    bool decorates(IPattern *pattern);

private:
    void init();

    IPattern *mPattern;

    vector<vector<CvPoint2D32f>>* mImgPoints;
    vector<vector<CvPoint2D32f>>* mFramePoints;
};

}}}};