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

using namespace baluchon::utilities;

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

		CvScalar color = markers[i]->getColor();
		vector<IBlob*> blobs = markers[i]->getBlobs();
		for (unsigned int j = 0; j < blobs.size(); j++) {
			cvDrawContours(initial, blobs[j]->getContours(), CV_RGB(255, 0, 0), color, -1, 5, 8);

			cvDrawCircle(initial, blobs[j]->getPosition(), 5, CV_RGB(0, 255, 0), -1, 8);

			if (j < blobs.size() - 1)
				cvDrawLine(initial, blobs[j]->getPosition(), blobs[j+1]->getPosition(), CV_RGB(0, 0, 255), 2, 8);
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
		IplImage* hsv = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);
		cvCvtColor(img, hsv, CV_BGR2HSV);

		CvScalar colorImageBGR = cvGet2D(img, y, x);
		CvScalar colorImageHSV = cvGet2D(hsv, y, x);
		
		IMarker* wMarker = new Marker();
		{
			wMarker->setColor(colorImageHSV);
		}

		wDisplayService->mMarkerService->addMarker(wMarker);
	}
}

}}}};