#include "Translation.h"

namespace baluchon { namespace core { namespace services { namespace positioning { 

Translation::Translation(CvPoint3D32f vector)
{
    cvmSet(mMat, 0, 3, vector.x);
    cvmSet(mTransformedMat, 0, 3, vector.x);
    cvmSet(mMat, 1, 3, vector.y);
    cvmSet(mTransformedMat, 1, 3, vector.y);
    cvmSet(mMat, 2, 3, vector.z);
    cvmSet(mTransformedMat, 2, 3, vector.z);
}


Translation::~Translation(void)
{
}

}}}};