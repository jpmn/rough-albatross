#include "AnimatedTranslation.h"

namespace baluchon { namespace core { namespace datas { namespace animation {

AnimatedTranslation::AnimatedTranslation(CvPoint3D32f vector, CvPoint3D32f increment) {
	mVector = vector;
	mIncrement = increment;
}

AnimatedTranslation::~AnimatedTranslation(void) {

}

void AnimatedTranslation::applyIncrement(void) {

	cvmSet(mMat, 0, 3, mVector.x);
    cvmSet(mTransformedMat, 0, 3, mVector.x);
    cvmSet(mMat, 1, 3, mVector.y);
    cvmSet(mTransformedMat, 1, 3, mVector.y);
    cvmSet(mMat, 2, 3, mVector.z);
    cvmSet(mTransformedMat, 2, 3, mVector.z);

	if (mVector.x != 0)
		mVector.x += mIncrement.x;

	if (mVector.y != 0)
		mVector.y += mIncrement.y;

	if (mVector.z != 0)
		mVector.z += mIncrement.z;
}

}}}};