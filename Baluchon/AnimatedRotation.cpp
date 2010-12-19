#include "AnimatedRotation.h"

namespace baluchon { namespace core { namespace datas { namespace animation {

AnimatedRotation::AnimatedRotation(CvPoint3D32f axis, float angle, float increment) {
	mAxis = axis;
	mAngle = angle;
	mIncrement = increment;
}

AnimatedRotation::~AnimatedRotation(void) {

}

void AnimatedRotation::applyIncrement(void) {

	double degToRad =  3.1415926535897932384626433832795 / 180.0f;

	double oneMinusCosAngle = 1-cos(degToRad*mAngle);
	double sinAngle = sin(degToRad*mAngle);
    
    cvmSet(mMat, 0, 0, 1+oneMinusCosAngle*(mAxis.x*mAxis.x-1));
    cvmSet(mTransformedMat, 0, 0, 1+oneMinusCosAngle*(mAxis.x*mAxis.x-1));

    cvmSet(mMat, 0, 1, -mAxis.z*sinAngle+oneMinusCosAngle*mAxis.x*mAxis.y);
    cvmSet(mTransformedMat, 0, 1, -mAxis.z*sinAngle+oneMinusCosAngle*mAxis.x*mAxis.y);

    cvmSet(mMat, 0, 2, mAxis.y*sinAngle+oneMinusCosAngle*mAxis.x*mAxis.z);
    cvmSet(mTransformedMat, 0, 2, mAxis.y*sinAngle+oneMinusCosAngle*mAxis.x*mAxis.z);

    cvmSet(mMat, 1, 0, mAxis.z*sinAngle+oneMinusCosAngle*mAxis.x*mAxis.y);
    cvmSet(mTransformedMat, 1, 0, mAxis.z*sinAngle+oneMinusCosAngle*mAxis.x*mAxis.y);

    cvmSet(mMat, 1, 1, 1+oneMinusCosAngle*(mAxis.y*mAxis.y-1));
    cvmSet(mTransformedMat, 1, 1, 1+oneMinusCosAngle*(mAxis.y*mAxis.y-1));

    cvmSet(mMat, 1, 2, -mAxis.x*sinAngle+oneMinusCosAngle*mAxis.y*mAxis.z);
    cvmSet(mTransformedMat, 1, 2, -mAxis.x*sinAngle+oneMinusCosAngle*mAxis.y*mAxis.z);

    cvmSet(mMat, 2, 0, -mAxis.y*sinAngle+oneMinusCosAngle*mAxis.x*mAxis.z);
    cvmSet(mTransformedMat, 2, 0, -mAxis.y*sinAngle+oneMinusCosAngle*mAxis.x*mAxis.z);

    cvmSet(mMat, 2, 1, mAxis.x*sinAngle+oneMinusCosAngle*mAxis.y*mAxis.z);
    cvmSet(mTransformedMat, 2, 1, mAxis.x*sinAngle+oneMinusCosAngle*mAxis.y*mAxis.z);

    cvmSet(mMat, 2, 2, 1+oneMinusCosAngle*(mAxis.z*mAxis.z-1));
    cvmSet(mTransformedMat, 2, 2, 1+oneMinusCosAngle*(mAxis.z*mAxis.z-1));

	mAngle = (float)((int)(mAngle + mIncrement) % 360);
}

}}}};