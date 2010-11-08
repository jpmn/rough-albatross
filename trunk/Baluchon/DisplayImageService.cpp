#include <typeinfo>

#include <highgui.h>

#include "DisplayImageService.h"
#include "IServiceLayer.h"

#include "CameraCaptureService.h"

namespace baluchon { namespace core { namespace services { namespace implementations {

DisplayImageService::DisplayImageService(void) {

}

DisplayImageService::~DisplayImageService(void) {

}

void DisplayImageService::init(void) {
    mCaptureService= new CameraCaptureService();
    mCaptureService = (ICaptureService*) mServiceLayer->findService(mCaptureService);
}

void DisplayImageService::initDone(void) {
	cvNamedWindow(mWindowName, 1);
}

void DisplayImageService::execute(void) {
	cvShowImage(mWindowName, mCaptureService->getImage());
}

void DisplayImageService::reset(void) {

}

void DisplayImageService::dispose(void) {
	cvDestroyWindow(mWindowName);
}

void DisplayImageService::setWindowName(char* name) {
	mWindowName = name;
}

}}}};