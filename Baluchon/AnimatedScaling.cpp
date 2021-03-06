#include "AnimatedScaling.h"

namespace baluchon { namespace core { namespace datas { namespace animation {

AnimatedScaling::AnimatedScaling(CvPoint3D32f factors, CvPoint3D32f increment) {
	mFactors = factors;
	mIncrement = increment;
}

AnimatedScaling::~AnimatedScaling(void) {

}

void AnimatedScaling::applyIncrement(void) {

	cvmSet(mMat, 0, 0, mFactors.x);
    cvmSet(mMat, 1, 1, mFactors.y);
    cvmSet(mMat, 2, 2, mFactors.z);

	mFactors.x *= mIncrement.x;
	mFactors.y *= mIncrement.y;
	mFactors.z *= mIncrement.z;
}

}}}};