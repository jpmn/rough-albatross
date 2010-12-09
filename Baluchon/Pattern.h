#pragma once
#include "ipattern.h"

namespace baluchon { namespace core { namespace services { namespace patterndetection { 

class Pattern :
    public IPattern
{
public:
    Pattern(char path[]);
    ~Pattern(void);

    int getWidth();
    int getHeight();
    int getPointCount();
    CvPoint2D32f getSourcePointAt(int pos, int orientation = 0);

private:
    void init();

    int mWidth;
    int mHeight;
    int mPointCount;
    char* mPath;
    CvPoint2D32f (*mSrcPoints)[4];
    /*vector<vector<CvPoint2D32f>>* mImgPoints;
    vector<vector<CvPoint2D32f>>* mFramePoints;
    vector<int>* mOrientations;*/
};

}}}};