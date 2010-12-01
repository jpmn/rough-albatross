#include "ColorDetectionService.h"
#include "IServiceLayer.h"
#include "CameraCaptureService.h"

namespace baluchon { namespace core { namespace services { namespace colordetection {

ColorDetectionService::ColorDetectionService(void) {
	
}

ColorDetectionService::~ColorDetectionService(void) {
	clearMarkers();
}

void ColorDetectionService::init(void) {
	mCaptureService = new CameraCaptureService();
    mCaptureService = (ICaptureService*) mServiceLayer->findService(mCaptureService);
}

void ColorDetectionService::initDone(void) {
	mImageHSV = cvCreateImage(mCaptureService->getSize(), IPL_DEPTH_8U, 3);
}

void ColorDetectionService::execute(void) {

	if (mMarkers.size() == 0) {
		return;
	}

	IplImage* imgIn = mCaptureService->getImage();
	
	/*
	IplImage* gray = cvCreateImage(mCaptureService->getSize(), 8, 1);
	
	cvSplit(imgIn, gray, NULL, NULL, NULL);
	cvEqualizeHist(gray, gray);
	cvMerge(gray, NULL, NULL, NULL, imgIn);

	cvSplit(imgIn, NULL, gray, NULL, NULL);
	cvEqualizeHist(gray, gray);
	cvMerge(NULL, gray, NULL, NULL, imgIn);

	cvSplit(imgIn, NULL, NULL, gray, NULL);
	cvEqualizeHist(gray, gray);
	cvMerge(NULL, NULL, gray, NULL, imgIn);
	
	cvReleaseImage(&gray);
	*/

	cvCvtColor(imgIn, mImageHSV, CV_BGR2HSV);

	for (unsigned int i = 0; i < mMarkers.size(); i++) {

		mMarkers[i]->clearBlobs();

		mMarkers[i]->findBlobs(mImageHSV);
	}
}

void ColorDetectionService::reset(void) {

}

void ColorDetectionService::dispose(void) {
	cvReleaseImage(&mImageHSV);
}

void ColorDetectionService::addMarker(IMarker* marker) {
	if (mMarkers.size() == mMaxMarkerCount) {
		mMarkers.erase(mMarkers.begin());
	}

	mMarkers.push_back(marker);
}

vector<IMarker*> ColorDetectionService::getMarkers(void) {
	return mMarkers;
}

void ColorDetectionService::clearMarkers(void) {
	for (unsigned int i = 0; i < mMarkers.size(); i++) {
		delete mMarkers[i];
	}
	mMarkers.clear();
}

void ColorDetectionService::setMaxMarkerCount(int count) {
	mMaxMarkerCount = count;
}

int ColorDetectionService::getMaxMarkerCount(void) {
	return mMaxMarkerCount;
}

}}}};