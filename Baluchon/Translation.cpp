#include "Translation.h"

namespace baluchon { namespace core { namespace services { namespace positioning { 

Translation::Translation(int x, int y, int z)
{
    cvmSet(mMat, 0, 3, x);
    cvmSet(mTransformedMat, 0, 3, x);
    cvmSet(mMat, 1, 3, y);
    cvmSet(mTransformedMat, 1, 3, y);
    cvmSet(mMat, 2, 3, z);
    cvmSet(mTransformedMat, 2, 3, z);
}


Translation::~Translation(void)
{
}

}}}};