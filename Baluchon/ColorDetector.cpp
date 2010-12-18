#include "ColorDetector.h"

#include "ColorUtility.h"

using namespace baluchon::utilities;

namespace baluchon { namespace core { namespace services { namespace colordetection {

ColorDetector::ColorDetector(void) {
	mStorage = cvCreateMemStorage(0);

	mMorphKernel = cvCreateStructuringElementEx(3, 3, 1, 1, CV_SHAPE_CROSS);

	mMarkerFactory = new MarkerFactory();

	mMinimumSize = 100;
}

ColorDetector::~ColorDetector(void) {
	cvReleaseMemStorage(&mStorage);

	cvReleaseStructuringElement(&mMorphKernel);
}

vector<IDetectable*> ColorDetector::find(IplImage* img, IplImage* src) {

	mImageThreshold = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);

	vector<IDetectable*> wListDetectables;

	for (unsigned int i = 0; i < mListColors.size(); i++) {
		CvScalar wColor = mListColors[i];
		int wTolerance = mListColorsTolerance[i];

		CvScalar wColorHSV = ColorUtility::convertColorBGRtoHSV(wColor);

		// Applique un threshold sur la couleur en tenant compte de la tolérance
		cvInRangeS(
			img, 
			cvScalar(wColorHSV.val[0] - wTolerance, wColorHSV.val[1] - wTolerance, 100),
			cvScalar(wColorHSV.val[0] + wTolerance, wColorHSV.val[1] + wTolerance, 255),
			mImageThreshold
		);

		// Applique un dilate et erode pour éliminer le bruit
		cvMorphologyEx(mImageThreshold, mImageThreshold, NULL, mMorphKernel, CV_MOP_OPEN, 1);

		//cvShowImage("Threshold", mImageThreshold);

		mContours = NULL;
		mContoursApprox = NULL;
		mContoursBiggest = NULL;
		double wContoursBiggestAreaSize = mMinimumSize;

		cvClearMemStorage(mStorage);

		// Trouve les contours dans l'image en niveaux de gris retournée par le threshold
		cvFindContours(mImageThreshold, mStorage, &mContours, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

		cvZero(mImageThreshold);

		while (mContours != NULL) {
			mContoursApprox = cvApproxPoly(mContours, sizeof(CvContour), mStorage, CV_POLY_APPROX_DP, cvContourPerimeter(mContours)*0.02, 0);

			double wContourAreaSize = fabs(cvContourArea(mContoursApprox, CV_WHOLE_SEQ));
			
			if (wContourAreaSize > wContoursBiggestAreaSize) {

				wContoursBiggestAreaSize = wContourAreaSize;
				mContoursBiggest = mContoursApprox;
			}

			mContours = mContours->h_next;
		}

		if (mContoursBiggest) {
			ColoredMarker* marker = mMarkerFactory->createColoredMarker(mContoursApprox, wColor, wTolerance);

			wListDetectables.push_back(marker);
		}
	}

	cvReleaseImage(&mImageThreshold);

	return wListDetectables;
}

void ColorDetector::addColor(CvScalar color, int tolerance) {
	mListColors.push_back(color);
	mListColorsTolerance.push_back(tolerance);
}

void ColorDetector::setMaxMarkerCount(int count) {
	mMaxMarkerCount = count;
}

int ColorDetector::getMaxMarkerCount(void) {
	return mMaxMarkerCount;
}

void ColorDetector::setMinimumSize(int size) {
	mMinimumSize = size;
}

int ColorDetector::getMinimumSize(void) {
	return mMinimumSize;
}

}}}};