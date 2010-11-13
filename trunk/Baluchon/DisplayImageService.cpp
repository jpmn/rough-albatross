#include <cv.h>

#include "DisplayImageService.h"
#include "IServiceLayer.h"

#include "CameraCaptureService.h"
#include "ColorDetectionService.h"
#include "PatternDetectionService.h"

#include "IPattern.h"
#include "Marker.h"
#include "Blob.h"
#include "ColorUtility.h"

namespace baluchon { namespace core { namespace services { namespace display {

DisplayImageService::DisplayImageService(void) {

}

DisplayImageService::~DisplayImageService(void) {

}

void DisplayImageService::init(void) {
    mCaptureService = new CameraCaptureService();
    mCaptureService = (ICaptureService*) mServiceLayer->findService(mCaptureService);

	mMarkerService = new ColorDetectionService();
	mMarkerService = (IColorDetectionService*) mServiceLayer->findService(mMarkerService);

    mPatternService= new PatternDetectionService();
    mPatternService = (IPatternDetectionService*) mServiceLayer->findService(mPatternService);
}

void DisplayImageService::initDone(void) {
	cvNamedWindow(mWindowName, 1);

	cvSetMouseCallback(mWindowName, (CvMouseCallback)DisplayImageService::onMouseClick, (void*)this);
}

void DisplayImageService::execute(void) {

    IplImage *initial = mCaptureService->getImage();

    //temporaire...juste pour faire le showoff
    vector<IPattern*> patterns = mPatternService->getPatterns();
    for(int i = 0; i < patterns.size(); i++)
    {
        for(int j = 0; j < (*patterns[i]->getImagePoints()).size(); j++)
        {
            for(int k = 0; k < (*patterns[i]->getImagePoints())[j].size(); k++)
            {
                cvLine(initial, cvPoint((*patterns[i]->getImagePoints())[j][k].x, (*patterns[i]->getImagePoints())[j][k].y), cvPoint((*patterns[i]->getImagePoints())[j][(k+1) % (*patterns[i]->getImagePoints())[j].size()].x, (*patterns[i]->getImagePoints())[j][(k+1) % (*patterns[i]->getImagePoints())[j].size()].y), CV_RGB(255,0,0,0), 5);
            }
        }
    }

	// temporaire... juste pour afficher les blobs
	vector<IMarker*> markers = mMarkerService->getMarkers();
	for (unsigned int i = 0; i < markers.size(); i++) {

		vector<IBlob*> blobs = markers[i]->getBlobs();
		for (unsigned int j = 0; j < blobs.size(); j++) {
			cvDrawContours(initial, blobs[i]->getContour(), markers[i]->getColor(), markers[i]->getColor(), -1, CV_FILLED, 8);

			cvDrawCircle(initial, blobs[i]->getPosition(), 5, CV_RGB(255, 0, 0), -1, 8);
		}
	}

	cvShowImage(mWindowName, initial);

	mImage = initial;
}

void DisplayImageService::reset(void) {

}

void DisplayImageService::dispose(void) {
	cvDestroyWindow(mWindowName);

	delete mCaptureService;
	delete mMarkerService;
	delete mPatternService;
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
		IplImage* hsv = cvCloneImage(img);
		//cvCvtColor(img, hsv, CV_BGR2HSV);
		baluchon::utilities::ColorUtility::convertImageRGBtoHSV(img, hsv);

		CvScalar tmp = cvGet2D(img, y, x);
		CvScalar color = cvScalar(tmp.val[2], tmp.val[1], tmp.val[0]);
		tmp = cvGet2D(hsv, y, x);
		CvScalar colorMarkerHSV = baluchon::utilities::ColorUtility::convertRGB2HSV(color);

		cvReleaseImage(&hsv);

		IColorDetectionService* service = wDisplayService->mMarkerService;
		vector<IMarker*> markers = service->getMarkers();
		int tolerance = service->getColorTolerance();
		bool found = false;

		for (unsigned int i = 0; i < markers.size(); i++) {
			if (fabs(markers[i]->getColor().val[0] - color.val[0]) <= tolerance &&
				fabs(markers[i]->getColor().val[1] - color.val[1]) <= tolerance) {
					found = true;
					break;
			}
		}

		if (!found) {
			IMarker* wMarker = new Marker();
			{
				wMarker->setColor(color);
			}

			service->addMarker(wMarker);
		}

	}
}

}}}};