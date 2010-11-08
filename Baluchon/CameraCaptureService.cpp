#include "CameraCaptureService.h"

namespace Baluchon { namespace Core { namespace Services { namespace Implementations {

CameraCaptureService::CameraCaptureService(void) {

}

CameraCaptureService::~CameraCaptureService(void) {

}

void CameraCaptureService::Init(void) {

}

void CameraCaptureService::InitDone(void) {

}

void CameraCaptureService::Execute(void) {
	mImage = cvQueryFrame(mCameraCapture);
}

void CameraCaptureService::Reset(void) {

}

void CameraCaptureService::Dispose(void) {

}

void CameraCaptureService::SetCapture(CvCapture* capture) {
	mCameraCapture = capture;
}

IplImage* CameraCaptureService::GetImage(void) {
	return mImage;
}

}}}};