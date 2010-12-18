#include "ColorDetectionService.h"
#include "IServiceLayer.h"
#include "CameraCaptureService.h"
#include "ColoredMarker.h"

namespace baluchon { namespace core { namespace services { namespace colordetection {

ColorDetectionService::ColorDetectionService(void) {
	
}

ColorDetectionService::~ColorDetectionService(void) {

}

void ColorDetectionService::init(void) {
	mCaptureService = new CameraCaptureService();
    mCaptureService = (ICaptureService*) mServiceLayer->findService(mCaptureService);
}

void ColorDetectionService::initDone(void) {

	mImageHSV = cvCreateImage(mCaptureService->getSize(), IPL_DEPTH_8U, 3);
}

void ColorDetectionService::execute(void) {

	IplImage* imgIn = mCaptureService->getImage();

	cvCvtColor(imgIn, mImageHSV, CV_BGR2HSV);

	mListDetectables.clear();

	for (unsigned int i = 0; i < mListDetectors.size(); i++) {
		vector<IDetectable*> wListDetectables = mListDetectors[i]->find(mImageHSV, imgIn);

		for (unsigned int j = 0; j < wListDetectables.size(); j++)
			mListDetectables.push_back(wListDetectables[j]);
	}
}

void ColorDetectionService::reset(void) {

}

void ColorDetectionService::dispose(void) {
	cvReleaseImage(&mImageHSV);
}

}}}};