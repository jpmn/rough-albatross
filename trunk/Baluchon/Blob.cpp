#include "Blob.h"

namespace baluchon {  namespace core { namespace datas { namespace detection {

Blob::Blob(void) {
	mStorage = cvCreateMemStorage(0);
}

Blob::~Blob(void) {
	cvReleaseMemStorage(&mStorage);
}

void Blob::setContours(CvSeq* contours) {
	cvClearMemStorage(mStorage);

	mContours = cvCloneSeq(contours, mStorage);
}

CvSeq* Blob::getContours(void) {
	return mContours;	
}

}}}};