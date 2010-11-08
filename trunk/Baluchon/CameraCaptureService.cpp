#include "CameraCaptureService.h"

namespace baluchon { namespace core { namespace services { namespace implementations {

CameraCaptureService::CameraCaptureService(void) {

}

CameraCaptureService::~CameraCaptureService(void) {

}

void CameraCaptureService::init(void) {

}

void CameraCaptureService::initDone(void) {

}

void CameraCaptureService::execute(void) {
	mImage = cvQueryFrame(mCameraCapture);
}

void CameraCaptureService::reset(void) {

}

void CameraCaptureService::dispose(void) {

}

void CameraCaptureService::setCapture(CvCapture* capture) {
	mCameraCapture = capture;
}

IplImage* CameraCaptureService::getImage(void) {
	return mImage;
}

}}}};