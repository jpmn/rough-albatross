#include "CameraCaptureService.h"

namespace baluchon { namespace core { namespace services { namespace capture {

CameraCaptureService::CameraCaptureService(void) {

}

CameraCaptureService::~CameraCaptureService(void) {

}

void CameraCaptureService::init(void) {

}

void CameraCaptureService::initDone(void) {

	mSize = cvSize(
		(int)cvGetCaptureProperty(mCameraCapture, CV_CAP_PROP_FRAME_WIDTH),
		(int)cvGetCaptureProperty(mCameraCapture, CV_CAP_PROP_FRAME_HEIGHT)
	);
}

void CameraCaptureService::execute(void) {
	mImage = cvQueryFrame(mCameraCapture);
}

void CameraCaptureService::reset(void) {

}

void CameraCaptureService::dispose(void) {
	cvReleaseCapture(&mCameraCapture);
}

void CameraCaptureService::setCapture(CvCapture* capture) {
	mCameraCapture = capture;
}

IplImage* CameraCaptureService::getImage(void) {
	return mImage;
}

CvSize CameraCaptureService::getSize(void) {
	return mSize;
}

}}}};