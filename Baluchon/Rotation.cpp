#include "Rotation.h"

namespace baluchon { namespace core { namespace services { namespace positioning {

Rotation::Rotation(float angle, float x, float y, float z)
{
    double degToRad =  3.1415926535897932384626433832795 / 180.0f;
    
    cvmSet(mMat, 0, 0, 1+(1-cos(degToRad*angle))*(x*x-1));
    cvmSet(mTransformedMat, 0, 0, 1+(1-cos(degToRad*angle))*(x*x-1));

    cvmSet(mMat, 0, 1, -z*sin(degToRad*angle)+(1-cos(degToRad*angle))*x*y);
    cvmSet(mTransformedMat, 0, 1, -z*sin(degToRad*angle)+(1-cos(degToRad*angle))*x*y);

    cvmSet(mMat, 0, 2, y*sin(degToRad*angle)+(1-cos(degToRad*angle))*x*z);
    cvmSet(mTransformedMat, 0, 2, y*sin(degToRad*angle)+(1-cos(degToRad*angle))*x*z);

    cvmSet(mMat, 1, 0, z*sin(degToRad*angle)+(1-cos(degToRad*angle))*x*y);
    cvmSet(mTransformedMat, 1, 0, z*sin(degToRad*angle)+(1-cos(degToRad*angle))*x*y);

    cvmSet(mMat, 1, 1, 1+(1-cos(degToRad*angle))*(y*y-1));
    cvmSet(mTransformedMat, 1, 1, 1+(1-cos(degToRad*angle))*(y*y-1));

    cvmSet(mMat, 1, 2, -x*sin(degToRad*angle)+(1-cos(degToRad*angle))*y*z);
    cvmSet(mTransformedMat, 1, 2, -x*sin(degToRad*angle)+(1-cos(degToRad*angle))*y*z);

    cvmSet(mMat, 2, 0, -y*sin(degToRad*angle)+(1-cos(degToRad*angle))*x*z);
    cvmSet(mTransformedMat, 2, 0, -y*sin(degToRad*angle)+(1-cos(degToRad*angle))*x*z);

    cvmSet(mMat, 2, 1, x*sin(degToRad*angle)+(1-cos(degToRad*angle))*y*z);
    cvmSet(mTransformedMat, 2, 1, x*sin(degToRad*angle)+(1-cos(degToRad*angle))*y*z);

    cvmSet(mMat, 2, 2, 1+(1-cos(degToRad*angle))*(z*z-1));
    cvmSet(mTransformedMat, 2, 2, 1+(1-cos(degToRad*angle))*(z*z-1));
}


Rotation::~Rotation(void)
{
}

}}}};
