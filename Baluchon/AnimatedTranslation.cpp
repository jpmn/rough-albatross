#include "AnimatedTranslation.h"

namespace baluchon { namespace core { namespace datas { namespace animation {

AnimatedTranslation::AnimatedTranslation(CvPoint3D32f vector, float increment) {
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

	mVector.x += mIncrement;
	mVector.y += mIncrement;
	mVector.z += mIncrement;
}

}}}};