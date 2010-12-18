#include "ObjectDetectionService.h"

#include <cv.h>

#include "IServiceLayer.h"
#include "CameraCaptureService.h"

#include "BoxDetector.h"

namespace baluchon { namespace core { namespace services { namespace objectdetection {

ObjectDetectionService::ObjectDetectionService(void) {

}

ObjectDetectionService::~ObjectDetectionService(void) {
	
}

void ObjectDetectionService::init(void) {
	mCaptureService = new CameraCaptureService();
	mCaptureService = (ICaptureService*) mServiceLayer->findService(mCaptureService);
}

void ObjectDetectionService::initDone(void) {
	//cvNamedWindow("Gray", 1);
	//cvNamedWindow("Canny", 1);
	
	mImageHSV = cvCreateImage(mCaptureService->getSize(), IPL_DEPTH_8U, 3);
	mImageGray = cvCreateImage(mCaptureService->getSize(), IPL_DEPTH_8U, 1);
	mImageContours = cvCreateImage(mCaptureService->getSize(), IPL_DEPTH_8U, 1);

	mMorphKernel = cvCreateStructuringElementEx(7, 7, 1, 1, CV_SHAPE_ELLIPSE);
}

void ObjectDetectionService::execute(void) {
	IplImage* imgIn = mCaptureService->getImage();

	cvCvtColor(imgIn, mImageGray, CV_BGR2GRAY);

	cvSmooth(mImageGray, mImageGray, CV_MEDIAN, 7, 7);
	//cvShowImage("Gray", mImageGray);

	cvCanny(mImageGray, mImageContours, 400, 800, 5);
	cvDilate(mImageContours, mImageContours, mMorphKernel, 1);
	//cvShowImage("Canny", mImageContours);

	mListDetectables.clear();

	for (unsigned int i = 0; i < mListDetectors.size(); i++) {
		vector<IDetectable*> wListDetectables = mListDetectors[i]->find(mImageContours, imgIn);

		for (unsigned int j = 0; j < wListDetectables.size(); j++)
			mListDetectables.push_back(wListDetectables[j]);
	}
}

void ObjectDetectionService::reset(void) {

}

void ObjectDetectionService::dispose(void) {
	//cvDestroyWindow("Gray");
	//cvDestroyWindow("Canny");

	cvReleaseStructuringElement(&mMorphKernel);
	cvReleaseImage(&mImageContours);
	cvReleaseImage(&mImageGray);
	cvReleaseImage(&mImageHSV);
}

}}}};