#include "ColorDetectionService.h"
#include "CameraCaptureService.h"
#include "ColorUtility.h"
#include "Blob.h"

using namespace baluchon::utilities;

namespace baluchon { namespace core { namespace services { namespace colordetection {

ColorDetectionService::ColorDetectionService(void) {
	
}

ColorDetectionService::~ColorDetectionService(void) {
	clearMarkers();
}

void ColorDetectionService::init(void) {
	mCaptureService = new CameraCaptureService();
    mCaptureService = (ICaptureService*) mServiceLayer->findService(mCaptureService);
}

void ColorDetectionService::initDone(void) {
	mStorage = cvCreateMemStorage(0);

	mMorphKernel = cvCreateStructuringElementEx(5, 5, 1, 1, CV_SHAPE_RECT);

	mImageHSV = cvCreateImage(mCaptureService->getSize(), IPL_DEPTH_8U, 3);
	mImageThreshold = cvCreateImage(mCaptureService->getSize(), IPL_DEPTH_8U, 1);

	cvNamedWindow("Canny", 1);
	cvNamedWindow("HSV", 1);
}

void ColorDetectionService::execute(void) {

	if (mMarkers.size() == 0) {
		return;
	}

	IplImage* imgIn = mCaptureService->getImage();
	cvCvtColor(imgIn, mImageHSV, CV_BGR2HSV);

	//ColorUtility::convertImageBGRtoHSV(imgIn, mImageHSV);

	for (unsigned int i = 0; i < mMarkers.size(); i++) {

		mMarkers[i]->clearBlobs();

		CvScalar colorMarkerHSV = ColorUtility::convertColorBGRtoHSV(mMarkers[i]->getColor());

		// Applique un threshold sur la couleur en tenant compte de la tolérance
		cvInRangeS(
			mImageHSV, 
			cvScalar(colorMarkerHSV.val[0] - mColorTolerance, 100, 100),
			cvScalar(colorMarkerHSV.val[0] + mColorTolerance, 255, 255),
			mImageThreshold
		);

		// Applique un dilate et erode pour éliminer le bruit
		cvMorphologyEx(mImageThreshold, mImageThreshold, NULL, mMorphKernel, CV_MOP_OPEN, 1);

		//cvCanny(mImageThreshold, mImageThreshold, 0, 10, 5);

		cvShowImage("Canny", mImageThreshold);
		cvShowImage("HSV", mImageHSV);

		mContours = NULL;
		mContoursApprox = NULL;
		cvClearMemStorage(mStorage);

		// Trouve les contours dans l'image en niveaux de gris retournée par le threshold
		cvFindContours(mImageThreshold, mStorage, &mContours, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

		cvZero(mImageThreshold);

		//vector<CvSeq*> seqs;
		double maxContourAreaSize = 0.0f;
		IBlob* biggestBlob = NULL;
		
		while (mContours != NULL) {
			mContoursApprox = cvApproxPoly(mContours, sizeof(CvContour), mStorage, CV_POLY_APPROX_DP, cvContourPerimeter(mContours)*0.02, 0);

			double wContourAreaSize = fabs(cvContourArea(mContoursApprox, CV_WHOLE_SEQ));
			
			if (wContourAreaSize > maxContourAreaSize && wContourAreaSize > 500.0f) {

				maxContourAreaSize = wContourAreaSize;

				CvPoint wPosition = cvPoint(0, 0);
				CvMoments moments;

				cvContourMoments(mContoursApprox, &moments); 

				wPosition.x = moments.m10 / moments.m00;
				wPosition.y = moments.m01 / moments.m00;

				if (mMarkers[i]->getBlobs().size() == 0) {
					biggestBlob = new Blob();
					{
						biggestBlob->setPosition(wPosition);
						biggestBlob->setContours(mContoursApprox);
					}
					
					mMarkers[i]->addBlob(biggestBlob);
				}
				else {
					biggestBlob = mMarkers[i]->getBlobs()[0];
					{
						biggestBlob->setPosition(wPosition);
						biggestBlob->setContours(mContoursApprox);
					}
				}
			}

			mContours = mContours->h_next;
		}
	}
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

void ColorDetectionService::clearMarkers(void) {
	for (unsigned int i = 0; i < mMarkers.size(); i++) {
		delete mMarkers[i];
	}
	mMarkers.clear();
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