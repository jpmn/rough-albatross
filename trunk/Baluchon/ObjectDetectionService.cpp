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
	cvNamedWindow("Gray", 1);
	cvNamedWindow("Canny", 1);
	cvNamedWindow("Contours", 1);

	mKernel = cvCreateStructuringElementEx(7, 7, 1, 1, CV_SHAPE_ELLIPSE);
}

void ObjectDetectionService::execute(void) {
	IplImage* imgIn = mCaptureService->getImage();

	IplImage* mImageHSV = cvCreateImage(cvGetSize(imgIn), IPL_DEPTH_8U, 3);
	IplImage* mImageGray = cvCreateImage(cvGetSize(imgIn), IPL_DEPTH_8U, 1);
	IplImage* mImageEdges = cvCreateImage(cvGetSize(imgIn), IPL_DEPTH_32F, 1);
	IplImage* mImageContours = cvCreateImage(cvGetSize(imgIn), IPL_DEPTH_8U, 1);
	IplImage* mImageColors = cvCreateImage(cvGetSize(imgIn), IPL_DEPTH_8U, 3);
	
	//cvCvtColor(imgIn, mImageHSV, CV_BGR2HSV);
	//cvSplit(mImageHSV, mImageGray, NULL, NULL, NULL);
	cvCvtColor(imgIn, mImageGray, CV_BGR2GRAY);

	//cvAdaptiveThreshold(mImageGray, mImageGray, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, 3); 
	//cvLaplace(mImageGray, mImageEdges, 7);
	//cvConvertScale(mImageEdges, mImageContours);
	//cvCanny(mImageGray, mImageContours, 0, 100, 3);

	cvSmooth(mImageGray, mImageGray, CV_MEDIAN, 7, 7);
	cvShowImage("Canny", mImageGray);
	cvCanny(mImageGray, mImageContours, 400, 800, 5);
	cvDilate(mImageContours, mImageContours, mKernel, 1);

	cvShowImage("Gray", mImageContours);

	mListDetectables.clear();

	for (unsigned int i = 0; i < mListDetectors.size(); i++) {
		vector<IDetectable*> wListDetectables = mListDetectors[i]->find(mImageContours, imgIn);

		for (unsigned int j = 0; j < wListDetectables.size(); j++) {
			mListDetectables.push_back(wListDetectables[j]);
		}
	}

	cvShowImage("Contours", mImageColors);
	
	cvReleaseImage(&mImageColors);
	cvReleaseImage(&mImageEdges);
	cvReleaseImage(&mImageContours);
	cvReleaseImage(&mImageGray);
	cvReleaseImage(&mImageHSV);
}

void ObjectDetectionService::reset(void) {

}

void ObjectDetectionService::dispose(void) {
	cvDestroyWindow("Gray");
	cvDestroyWindow("Canny");
	cvDestroyWindow("Contours");

	cvReleaseStructuringElement(&mKernel);
}

vector<IDetectable*> ObjectDetectionService::getListDetectables(void) {
	return mListDetectables;
}

void ObjectDetectionService::addDetector(IDetector* detector) {
	mListDetectors.push_back(detector);
}

}}}};