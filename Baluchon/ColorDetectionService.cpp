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
	//cvCvtColor(imgIn, mImageHSV, CV_BGR2HSV);
	baluchon::utilities::ColorUtility::convertImageRGBtoHSV(imgIn, mImageHSV);

	IplImage* imgMerge = cvCloneImage(mImageThreshold);

	for (unsigned int i = 0; i < mMarkers.size(); i++) {
		mMarkers[i]->clearBlobs();
		//mMarkers[i]->getBlobs().clear();

		CvScalar colorMarkerHSV = ColorUtility::convertRGB2HSV(mMarkers[i]->getColor());

		// Applique un threshold sur la couleur en tenant compte de la tolérance
		cvInRangeS(
			mImageHSV, 
			cvScalar(colorMarkerHSV.val[0] - mColorTolerance, 100, 100),//colorMarkerHSV.val[1] - mColorTolerance, 0), 
			cvScalar(colorMarkerHSV.val[0] + mColorTolerance, 255, 255),//colorMarkerHSV.val[1] + mColorTolerance, 255), 
			mImageThreshold
		);

		cvAdd(imgMerge, mImageThreshold, imgMerge);
		cvZero(mImageThreshold);
	}

	// Applique un dilate et erode pour éliminer le bruit
	cvMorphologyEx(imgMerge, imgMerge, NULL, mMorphKernel, CV_MOP_OPEN, 1);

	cvShowImage("Canny", imgMerge);

	//SHAPE_CANNY_EDGE_LINK, SHAPE_CANNY_EDGE_FIND, SHAPE_CANNY_APERTURE
	//cvCanny(imgMerge, imgMerge, 50, 100);

	CvSeq* contours = 0;
	CvSeq* approx = 0;

	// Trouve les contours dans l'image en niveaux de gris retournée par le threshold

	//mode : CV_RETR_EXTERNAL, CV_RETR_LIST, CV_RETR_CCOMP. method : CV_LINK_RUNS, CV_CHAIN_APPROX_SIMPLE
	int nb = cvFindContours(imgMerge, mStorage, &contours, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	while (contours != NULL) {
		approx = cvApproxPoly(contours, sizeof(CvContour), mStorage, CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0);

		//if (contours->flags & CV_SEQ_FLAG_CLOSED) {
		if (true) {
			double wContourAreaSize = fabs(cvContourArea(approx, CV_WHOLE_SEQ));

			//if (wContourAreaSize > 100.0) {
			//if (contours->total >= 10) {
			if (true) {
				// CV_FILLED
				cvDrawContours(imgIn, approx, cvScalar(255, 0, 0), cvScalar(255), -1, 5, 8);

				CvPoint wPosition = cvPoint(0, 0);
				CvMoments moments;

				cvContourMoments(approx, &moments); 

				wPosition.x = moments.m10 / moments.m00;
				wPosition.y = moments.m01 / moments.m00;

				cvDrawCircle(imgIn, wPosition, 5, CV_RGB(0, 255, 0), -1, 8);
				/*
				for (unsigned int i = 0; i < mMarkers.size(); i++) {
					CvPoint wPosition = cvPoint(0, 0);
					CvMoments moments;

					cvContourMoments(contours, &moments); 

					wPosition.x = moments.m10 / moments.m00;
					wPosition.y = moments.m01 / moments.m00;

					CvScalar colorImageHSV = cvGet2D(mImageHSV, wPosition.y, wPosition.x);
					CvScalar colorMarkerHSV = ColorUtility::convertRGB2HSV(mMarkers[i]->getColor());

					if (fabs(colorMarkerHSV.val[0] - colorImageHSV.val[0]) <= mColorTolerance &&
						fabs(colorMarkerHSV.val[1] - colorImageHSV.val[1]) <= mColorTolerance) {

						IBlob* blob = new Blob();
						{
							blob->setPosition(wPosition);
							blob->setContour(cvCloneSeq(contours));
						}
					
						mMarkers[i]->addBlob(blob);
					}
				}*/
			}
		}

		contours = contours->h_next;
	}

	cvShowImage("HSV", imgMerge);
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