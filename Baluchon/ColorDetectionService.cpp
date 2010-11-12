#include "ColorDetectionService.h"
#include "CameraCaptureService.h"
#include "ColorUtility.h"
#include "Blob.h"

using namespace baluchon::utilities;

namespace baluchon { namespace core { namespace services { namespace colordetection {

ColorDetectionService::ColorDetectionService(void) {
	
	mColorTolerance = 0;
	mMaxMarkerCount = 0;
}

ColorDetectionService::~ColorDetectionService(void) {
	for (unsigned int i = 0; i < mMarkers.size(); i++) {
		delete mMarkers[i];
	}

	mMarkers.clear();
}

void ColorDetectionService::init(void) {
	mCaptureService = new CameraCaptureService();
    mCaptureService = (ICaptureService*) mServiceLayer->findService(mCaptureService);
}

void ColorDetectionService::initDone(void) {
	mStorage = cvCreateMemStorage(0);

	mMorphKernel = cvCreateStructuringElementEx(5, 5, 1, 1, CV_SHAPE_RECT, NULL);

	mImageHSV = cvCreateImage(mCaptureService->getSize(), IPL_DEPTH_8U, 3);
	mImageThreshold = cvCreateImage(mCaptureService->getSize(), IPL_DEPTH_8U, 1);

	cvNamedWindow("Canny", 1);
	cvNamedWindow("HSV", 1);
}

void ColorDetectionService::execute(void) {

	if (mMarkers.size() == 0) {
		return;
	}

	cvClearMemStorage(mStorage);

	IplImage* imgIn = mCaptureService->getImage();
	cvCvtColor(imgIn, mImageHSV, CV_BGR2HSV);
	
	cvShowImage("HSV", mImageHSV);

	IplImage* imgMerge = cvCloneImage(mImageThreshold);

	for (unsigned int i = 0; i < mMarkers.size(); i++) {
		mMarkers[i]->clearBlobs();

		CvScalar colorMarkerHSV = ColorUtility::convertRGB2HSV(mMarkers[i]->getColor());

		// Applique un threshold sur la couleur en tenant compte de la tolérance
		cvInRangeS(
			mImageHSV, 
			cvScalar(colorMarkerHSV.val[0] - mColorTolerance, colorMarkerHSV.val[1] - mColorTolerance, 0), 
			cvScalar(colorMarkerHSV.val[0] + mColorTolerance, colorMarkerHSV.val[1] + mColorTolerance, 255), 
			mImageThreshold
		);

		// Applique un dilate et erode pour éliminer le bruit
		cvMorphologyEx(mImageThreshold, mImageThreshold, NULL, mMorphKernel, CV_MOP_OPEN, 1);

		cvAdd(imgMerge, mImageThreshold, imgMerge);
		cvZero(mImageThreshold);
	}

	//SHAPE_CANNY_EDGE_LINK, SHAPE_CANNY_EDGE_FIND, SHAPE_CANNY_APERTURE
	cvCanny(imgMerge, imgMerge, 50, 200, 3);

	cvShowImage("Canny", imgMerge);

	CvSeq* contour = 0;

	// Trouve les contours dans l'image en niveaux de gris retournée par le threshold

	//mode : CV_RETR_EXTERNAL, CV_RETR_LIST, CV_RETR_CCOMP. method : CV_LINK_RUNS, CV_CHAIN_APPROX_SIMPLE
	int nb = cvFindContours(imgMerge, mStorage, &contour, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	while (contour != NULL) {

		if (contour->flags & CV_SEQ_FLAG_CLOSED) {
			//double wContourAreaSize = cv::abs<float>(cvContourArea(contour, CV_WHOLE_SEQ));

			//if (wContourAreaSize > 50.0) {
			if (contour->total > 50.0) {
				for (unsigned int i = 0; i < mMarkers.size(); i++) {
					CvPoint wPosition = cvPoint(0, 0);
					CvMoments moments;

					cvContourMoments(contour, &moments); 

					wPosition.x = moments.m10 / moments.m00;
					wPosition.y = moments.m01 / moments.m00;

					CvScalar colorImageHSV = cvGet2D(mImageHSV, wPosition.y, wPosition.x);
					CvScalar colorMarkerHSV = ColorUtility::convertRGB2HSV(mMarkers[i]->getColor());
			
					if (cv::abs<int>(colorMarkerHSV.val[0] - colorImageHSV.val[0]) <= mColorTolerance &&
						cv::abs<int>(colorMarkerHSV.val[1] - colorImageHSV.val[1]) <= mColorTolerance) {

						IBlob* blob = new Blob();
						{
							blob->setPosition(wPosition);
							blob->setContour(cvCloneSeq(contour));
						}
					
						mMarkers[i]->addBlob(blob);
					}
				}
			}
		}

		contour = contour->h_next;
	}

	cvReleaseImage(&imgMerge);
}

void ColorDetectionService::reset(void) {

}

void ColorDetectionService::dispose(void) {
	cvReleaseMemStorage(&mStorage);
	cvReleaseImage(&mImageThreshold);
	cvReleaseImage(&mImageHSV);

	cvDestroyWindow("Canny");
	cvDestroyWindow("HSV");
}

void ColorDetectionService::addMarker(IMarker* marker) {
	if (mMarkers.size() == mMaxMarkerCount) {
		mMarkers.erase(mMarkers.begin());
	}

	mMarkers.push_back(marker);
}

vector<IMarker*> ColorDetectionService::getMarkers(void) {
	return mMarkers;
}

void ColorDetectionService::setColorTolerance(int tolerance) {
	mColorTolerance = tolerance;
}

int ColorDetectionService::getColorTolerance(void) {
	return mColorTolerance;
}

void ColorDetectionService::setMaxMarkerCount(int count) {
	mMaxMarkerCount = count;
}

int ColorDetectionService::getMaxMarkerCount(void) {
	return mMaxMarkerCount;
}

}}}};