#include "VideoWriterService.h"

namespace Baluchon { namespace Core { namespace Services {

CVideoWriterService::CVideoWriterService(void)
{
	mWriter = cvCreateVideoWriter("color-detection.avi", -1, 15, cvSize(640, 480));
}

CVideoWriterService::~CVideoWriterService(void)
{
	cvReleaseVideoWriter(&mWriter);
}

void CVideoWriterService::execute(IplImage* img) {
	cvWriteFrame(mWriter, img);
}

void CVideoWriterService::initialize(void) {

}

void CVideoWriterService::initializeDone(void) {

}

void CVideoWriterService::reset(void) {

}

}}};