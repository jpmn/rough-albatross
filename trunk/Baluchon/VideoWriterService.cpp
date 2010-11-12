#include "VideoWriterService.h"

#include "DisplayImageService.h"

namespace baluchon { namespace core { namespace services { namespace writer { 

VideoWriterService::VideoWriterService(void) {

}

VideoWriterService::~VideoWriterService(void) {

}

void VideoWriterService::init(void) {
	
    mDisplayService = new DisplayImageService();
    mDisplayService = (IDisplayService*) mServiceLayer->findService(mDisplayService);
}

void VideoWriterService::initDone(void) {

	if (isEnabled())
		mVideoWriter = cvCreateVideoWriter("color-detection.avi", -1, 8, cvSize(640, 480));
}

void VideoWriterService::execute(void) {

	cvWriteFrame(mVideoWriter, mDisplayService->getImage());
}

void VideoWriterService::reset(void) {

}

void VideoWriterService::dispose(void) {

	if (isEnabled())
		cvReleaseVideoWriter(&mVideoWriter);
}

}}}};