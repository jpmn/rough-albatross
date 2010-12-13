#include "Rotation.h"

namespace baluchon { namespace core { namespace services { namespace positioning {

Rotation::Rotation(float angle, CvPoint3D32f axis)
{
    double degToRad =  3.1415926535897932384626433832795 / 180.0f;
    
    cvmSet(mMat, 0, 0, 1+(1-cos(degToRad*angle))*(axis.x*axis.x-1));
    cvmSet(mTransformedMat, 0, 0, 1+(1-cos(degToRad*angle))*(axis.x*axis.x-1));

    cvmSet(mMat, 0, 1, -axis.z*sin(degToRad*angle)+(1-cos(degToRad*angle))*axis.x*axis.y);
    cvmSet(mTransformedMat, 0, 1, -axis.z*sin(degToRad*angle)+(1-cos(degToRad*angle))*axis.x*axis.y);

    cvmSet(mMat, 0, 2, axis.y*sin(degToRad*angle)+(1-cos(degToRad*angle))*axis.x*axis.z);
    cvmSet(mTransformedMat, 0, 2, axis.y*sin(degToRad*angle)+(1-cos(degToRad*angle))*axis.x*axis.z);

    cvmSet(mMat, 1, 0, axis.z*sin(degToRad*angle)+(1-cos(degToRad*angle))*axis.x*axis.y);
    cvmSet(mTransformedMat, 1, 0, axis.z*sin(degToRad*angle)+(1-cos(degToRad*angle))*axis.x*axis.y);

    cvmSet(mMat, 1, 1, 1+(1-cos(degToRad*angle))*(axis.y*axis.y-1));
    cvmSet(mTransformedMat, 1, 1, 1+(1-cos(degToRad*angle))*(axis.y*axis.y-1));

    cvmSet(mMat, 1, 2, -axis.x*sin(degToRad*angle)+(1-cos(degToRad*angle))*axis.y*axis.z);
    cvmSet(mTransformedMat, 1, 2, -axis.x*sin(degToRad*angle)+(1-cos(degToRad*angle))*axis.y*axis.z);

    cvmSet(mMat, 2, 0, -axis.y*sin(degToRad*angle)+(1-cos(degToRad*angle))*axis.x*axis.z);
    cvmSet(mTransformedMat, 2, 0, -axis.y*sin(degToRad*angle)+(1-cos(degToRad*angle))*axis.x*axis.z);

    cvmSet(mMat, 2, 1, axis.x*sin(degToRad*angle)+(1-cos(degToRad*angle))*axis.y*axis.z);
    cvmSet(mTransformedMat, 2, 1, axis.x*sin(degToRad*angle)+(1-cos(degToRad*angle))*axis.y*axis.z);

    cvmSet(mMat, 2, 2, 1+(1-cos(degToRad*angle))*(axis.z*axis.z-1));
    cvmSet(mTransformedMat, 2, 2, 1+(1-cos(degToRad*angle))*(axis.z*axis.z-1));
}


Rotation::~Rotation(void)
{
}

}}}};
