#pragma once
#include "ivisitor.h"
#include "cv.h"

namespace baluchon { namespace core { namespace services { namespace positioning { 

class FrameCube;
class Transform;

class PositioningVisitor :
    public IVisitor
{
public:
    PositioningVisitor(CvMat* intrinsicMat, CvMat* distortionMat);
    ~PositioningVisitor(void);

    void visit(FrameCube *fc);
    void visit(Transform *t);

    void setImage(IplImage* img);
    void setRotationMat(CvMat* rotation);
    void setTranslationMat(CvMat* translation);

protected:
    IplImage* mSrcImg;
    CvMat* mIntrinsicMat;
    CvMat* mDistortionMat;
    CvMat* mRotationMat;
    CvMat* mTranslationMat;
};

}}}};