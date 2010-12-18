#include <cv.h>

#include "DisplayImageService.h"
#include "IServiceLayer.h"

#include "CameraCaptureService.h"
#include "ColorDetectionService.h"

#include "ColoredMarker.h"
#include "ColorDetector.h"
#include "ColorUtility.h"

using namespace baluchon::utilities;

namespace baluchon { namespace core { namespace services { namespace display {

DisplayImageService::DisplayImageService(void) {

}

DisplayImageService::~DisplayImageService(void) {

}

void DisplayImageService::init(void) {
    mCaptureService = new CameraCaptureService();
    mCaptureService = (ICaptureService*) mServiceLayer->findService(mCaptureService);

	mColorDetectionService = new ColorDetectionService();
	mColorDetectionService = (IColorDetectionService*) mServiceLayer->findService(mColorDetectionService);
}

void DisplayImageService::initDone(void) {
	cvNamedWindow(mWindowName, 1);

	cvSetMouseCallback(mWindowName, (CvMouseCallback)DisplayImageService::onMouseClick, (void*)this);
}

void DisplayImageService::execute(void) {

    IplImage* initial = mCaptureService->getImage();

	vector<IDetectable*> wListDetectables = mColorDetectionService->getDetectables();

	for (unsigned int i = 0; i < wListDetectables.size(); i++) {
		ColoredMarker* wMarker = static_cast<ColoredMarker*>(wListDetectables[i]);
		
		//cvDrawContours(initial, blobs[j]->getContours(), CV_RGB(0, 0, 255), color, -1, 2, 8);

		CvRect box = cvBoundingRect(wMarker->getContours(), 1);
		cvDrawRect(initial, cvPoint(box.x, box.y), cvPoint(box.x + box.width, box.y + box.height), CV_RGB(255, 255, 0), 2, 8);
			
		cvDrawCircle(initial, wMarker->getPosition(), 5, CV_RGB(0, 255, 0), CV_FILLED, 8);
	}

	//cvFlip(initial, initial, 1);
	cvShowImage(mWindowName, initial);

	mImage = initial;
}

void DisplayImageService::reset(void) {

}

void DisplayImageService::dispose(void) {
	cvDestroyWindow(mWindowName);

	delete mCaptureService;
	delete mColorDetectionService;
}

void DisplayImageService::setWindowName(char* name) {
	mWindowName = name;
}

IplImage* DisplayImageService::getImage(void) {
	return mImage;
}

void DisplayImageService::onMouseClick(int event, int x, int y, int flags, void* param = NULL) {

	// temporairement pour setter des couleurs avec la souris
	if (event == CV_EVENT_LBUTTONUP) {
		DisplayImageService* wDisplayService = (DisplayImageService*)param;

		IplImage* img = wDisplayService->mCaptureService->getImage();
		
		CvScalar wColorBGR = cvGet2D(img, y, x);

		ColorDetector* wDetector = new ColorDetector();
		{
			wDetector->addColor(wColorBGR, 40);
		}

		wDisplayService->mColorDetectionService->addDetector(wDetector);
	}
}

}}}};