#include "FrameCube.h"

namespace baluchon { namespace core { namespace services { namespace positioning { 

FrameCube::FrameCube(CvPoint3D32f pt1, float size, CvScalar color)
{
    mInitialPoints.push_back(cvPoint3D32f(pt1.x, pt1.y, pt1.z + size));
    mTransformedPoints.push_back(cvPoint3D32f(pt1.x, pt1.y, pt1.z + size));
    mInitialPoints.push_back(cvPoint3D32f(pt1.x + size, pt1.y, pt1.z + size));
    mTransformedPoints.push_back(cvPoint3D32f(pt1.x + size, pt1.y, pt1.z + size));
    mInitialPoints.push_back(cvPoint3D32f(pt1.x + size, pt1.y + size, pt1.z + size));
    mTransformedPoints.push_back(cvPoint3D32f(pt1.x + size, pt1.y + size, pt1.z + size));
    mInitialPoints.push_back(cvPoint3D32f(pt1.x, pt1.y + size, pt1.z + size));
    mTransformedPoints.push_back(cvPoint3D32f(pt1.x, pt1.y + size, pt1.z + size));
    mInitialPoints.push_back(pt1);
    mTransformedPoints.push_back(pt1);
    mInitialPoints.push_back(cvPoint3D32f(pt1.x + size, pt1.y, pt1.z));
    mTransformedPoints.push_back(cvPoint3D32f(pt1.x + size, pt1.y, pt1.z));
    mInitialPoints.push_back(cvPoint3D32f(pt1.x + size, pt1.y + size, pt1.z));
    mTransformedPoints.push_back(cvPoint3D32f(pt1.x + size, pt1.y + size, pt1.z));
    mInitialPoints.push_back(cvPoint3D32f(pt1.x, pt1.y + size, pt1.z));
    mTransformedPoints.push_back(cvPoint3D32f(pt1.x, pt1.y + size, pt1.z));

    mColor = color;
}


FrameCube::~FrameCube(void)
{
}

void FrameCube::accept(IVisitor* v)
{   
    v->visit(this);
}

void FrameCube::setColor(CvScalar color)
{
    mColor = color;
}

CvScalar FrameCube::getColor()
{
    return mColor;
}

}}}};
