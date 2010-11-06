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

void CVideoWriterService::execute(const IplImage* imgIn, IplImage* imgOut) {
	cvWriteFrame(mWriter, imgIn);
}

void CVideoWriterService::initialize(void) {

}

void CVideoWriterService::initializeDone(void) {

}

void CVideoWriterService::reset(void) {

}

}}};