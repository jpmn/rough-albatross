#include "ColoredMarker.h"

#include "ColorUtility.h"

using namespace baluchon::utilities;

namespace baluchon { namespace core { namespace datas { namespace detection {

ColoredMarker::ColoredMarker(void) {
	mStorage = cvCreateMemStorage(0);
}

ColoredMarker::~ColoredMarker(void) {
	cvReleaseMemStorage(&mStorage);
}

void ColoredMarker::setContours(CvSeq* contours) {
	cvClearMemStorage(mStorage);

	mContours = cvCloneSeq(contours, mStorage);

	CvMoments moments;
	cvContourMoments(mContours, &moments); 

	mPosition.x = (int) (moments.m10 / moments.m00);
	mPosition.y = (int) (moments.m01 / moments.m00);
}

CvSeq* ColoredMarker::getContours(void) {
	return mContours;	
}

void ColoredMarker::setTolerance(int tolerance) {
	mTolerance = tolerance;
}

int ColoredMarker::getTolerance(void) {
	return mTolerance;
}

}}}};