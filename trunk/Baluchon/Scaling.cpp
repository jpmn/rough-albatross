#include "Scaling.h"

namespace baluchon { namespace core { namespace services { namespace positioning {

Scaling::Scaling(float x, float y, float z)
{
    cvmSet(mMat, 0, 0, x);
    cvmSet(mMat, 1, 1, y);
    cvmSet(mMat, 2, 2, z);
}


Scaling::~Scaling(void)
{
}

}}}};
