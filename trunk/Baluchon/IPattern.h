#pragma once

#include "cv.h"
#include "highgui.h"
#include <vector>

using namespace std;

namespace baluchon { namespace core { namespace services { namespace patterndetection { 

class IPattern
{
public:
    virtual ~IPattern(void) {};

    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
    virtual int getPointCount() = 0;
    virtual CvPoint2D32f getSourcePointAt(int pos, int orientation = 0) = 0;
    virtual vector<vector<CvPoint2D32f>>* getImagePoints() = 0;

};

}}}};