#include "AnimatedSliding.h"

namespace baluchon { namespace core { namespace datas { namespace animation {

AnimatedSliding::AnimatedSliding(CvPoint3D32f vector, CvPoint3D32f limit, CvPoint3D32f increment) {
	mVector = vector;
	mIncrement = increment;
	mInitial = vector;
	mLimit = limit;
}

AnimatedSliding::~AnimatedSliding(void) {

}

void AnimatedSliding::applyIncrement(void) {

	cvmSet(mMat, 0, 3, mVector.x);
    cvmSet(mTransformedMat, 0, 3, mVector.x);
    cvmSet(mMat, 1, 3, mVector.y);
    cvmSet(mTransformedMat, 1, 3, mVector.y);
    cvmSet(mMat, 2, 3, mVector.z);
    cvmSet(mTransformedMat, 2, 3, mVector.z);

	float x = mVector.x;
	if (mLimit.x != 0) {
		if (x > mInitial.x + mLimit.x)
			mSide.x = 1;
		else if (x < mInitial.x - mLimit.x)
			mSide.x = -1;

		if (mSide.x == 1)
			x -= mIncrement.x;
		else 
			x += mIncrement.x;
	}

	float y = mVector.y;
	if (mLimit.y != 0) {
		if (y > mInitial.y + mLimit.y)
			mSide.y = 1;
		else if (x < mInitial.y - mLimit.y)
			mSide.y = -1;

		if (mSide.y == 1)
			y -= mIncrement.y;
		else 
			y += mIncrement.y;
	}

	float z = mVector.z;
	if (mLimit.z != 0) {
		if (z > mInitial.z + mLimit.z)
			mSide.z = 1;
		else if (z < mInitial.z - mLimit.z || z < 0) // Limite du plancher... juste dans notre cas mettons.
			mSide.z = -1;

		if (mSide.z == 1)
			z -= mIncrement.z;
		else 
			z += mIncrement.z;
	}

	mVector.x = x;
	mVector.y = y;
	mVector.z = z;

}

}}}};