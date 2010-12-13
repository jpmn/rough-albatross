#include "Scaling.h"

namespace baluchon { namespace core { namespace services { namespace positioning {

Scaling::Scaling(CvPoint3D32f factors)
{
    cvmSet(mMat, 0, 0, factors.x);
    cvmSet(mMat, 1, 1, factors.y);
    cvmSet(mMat, 2, 2, factors.z);
}


Scaling::~Scaling(void)
{
}

}}}};
