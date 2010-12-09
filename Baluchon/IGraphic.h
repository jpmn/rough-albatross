#pragma once

#include <vector>
#include "cv.h"

using namespace std;

namespace baluchon { namespace core { namespace services { namespace positioning { 

class IVisitor;

class IGraphic
{
public:

    virtual ~IGraphic(void) {};

    virtual void accept(IVisitor* v) = 0;

    // transformation
    virtual void apply(CvMat* mul)
    {
        while(mTemporaryTransformedPoints.size() != mTransformedPoints.size())
        {
            mTemporaryTransformedPoints.push_back(cvPoint3D32f(0,0,0));
        }
        
        for(unsigned int j = 0; j < mTransformedPoints.size(); j++)
        {
            mTemporaryTransformedPoints[j].x = (float) (cvmGet(mul, 0, 0) * mTransformedPoints[j].x + cvmGet(mul, 0, 1) * mTransformedPoints[j].y + cvmGet(mul, 0, 2) * mTransformedPoints[j].z + cvmGet(mul, 0, 3));
            mTemporaryTransformedPoints[j].y = (float) (cvmGet(mul, 1, 0) * mTransformedPoints[j].x + cvmGet(mul, 1, 1) * mTransformedPoints[j].y + cvmGet(mul, 1, 2) * mTransformedPoints[j].z + cvmGet(mul, 1, 3));
            mTemporaryTransformedPoints[j].z = (float) (cvmGet(mul, 2, 0) * mTransformedPoints[j].x + cvmGet(mul, 2, 1) * mTransformedPoints[j].y + cvmGet(mul, 2, 2) * mTransformedPoints[j].z + cvmGet(mul, 2, 3));
        }

        for(unsigned int j = 0; j < mTransformedPoints.size(); j++)
        {
            mTransformedPoints[j].x = mTemporaryTransformedPoints[j].x;
            mTransformedPoints[j].y = mTemporaryTransformedPoints[j].y;
            mTransformedPoints[j].z = mTemporaryTransformedPoints[j].z;
        }
    }

    virtual vector<CvPoint3D32f> getPoints()
    {
        return mTransformedPoints;
    }

    virtual void reset()
    {
        mTransformedPoints.clear();
        for(unsigned int i = 0; i < mInitialPoints.size(); i++)
        {
            mTransformedPoints.push_back(mInitialPoints[i]);
        }
    }

protected:
    vector<CvPoint3D32f> mInitialPoints;
    vector<CvPoint3D32f> mTransformedPoints;
private:
    vector<CvPoint3D32f> mTemporaryTransformedPoints;
};

}}}};
