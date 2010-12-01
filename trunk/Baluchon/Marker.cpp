#include "Marker.h"

#include "ColorUtility.h"
#include "Blob.h"

using namespace baluchon::utilities;

namespace baluchon { namespace core { namespace services { namespace colordetection {

Marker::Marker(void) {
	mStorage = cvCreateMemStorage(0);

	mMorphKernel = cvCreateStructuringElementEx(3, 3, 1, 1, CV_SHAPE_CROSS, NULL);
}

Marker::~Marker(void) {
	clearBlobs();
	
	cvReleaseMemStorage(&mStorage);
	cvReleaseImage(&mImageThreshold);
}

void Marker::addBlob(IBlob* blob) {
	mBlobs.push_back(blob);
}

vector<IBlob*> Marker::getBlobs(void) {
	return mBlobs;
}

void Marker::clearBlobs(void) {
	for (unsigned int i = 0; i < mBlobs.size(); i++) {
		delete mBlobs[i];
	}
	mBlobs.clear();
}

void Marker::findBlobs(IplImage* img) {
	CvScalar colorMarkerHSV = ColorUtility::convertColorBGRtoHSV(mColor);

	mImageThreshold = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	
	// Applique un threshold sur la couleur en tenant compte de la tolérance
	cvInRangeS(
		img, 
		cvScalar(colorMarkerHSV.val[0] - mColorTolerance, colorMarkerHSV.val[1] - mColorTolerance, 100),
		cvScalar(colorMarkerHSV.val[0] + mColorTolerance, colorMarkerHSV.val[1] + mColorTolerance, 255),
		mImageThreshold
	);

	// Applique un dilate et erode pour éliminer le bruit
	cvMorphologyEx(mImageThreshold, mImageThreshold, NULL, mMorphKernel, CV_MOP_OPEN, 1);

	//cvShowImage("Threshold", mImageThreshold);

	mContours = NULL;
	mContoursApprox = NULL;
	cvClearMemStorage(mStorage);

	// Trouve les contours dans l'image en niveaux de gris retournée par le threshold
	cvFindContours(mImageThreshold, mStorage, &mContours, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	cvZero(mImageThreshold);

	double maxContourAreaSize = 0.0f;
	IBlob* biggestBlob = NULL;
		
	while (mContours != NULL) {
		mContoursApprox = cvApproxPoly(mContours, sizeof(CvContour), mStorage, CV_POLY_APPROX_DP, cvContourPerimeter(mContours)*0.02, 0);

		double wContourAreaSize = fabs(cvContourArea(mContoursApprox, CV_WHOLE_SEQ));
			
		if (wContourAreaSize > maxContourAreaSize && wContourAreaSize > 100.0f) {

			maxContourAreaSize = wContourAreaSize;

			CvPoint wPosition = cvPoint(0, 0);
			CvMoments moments;

			cvContourMoments(mContoursApprox, &moments); 

			wPosition.x = moments.m10 / moments.m00;
			wPosition.y = moments.m01 / moments.m00;

			if (mBlobs.size() == 0) {
				biggestBlob = new Blob();
				{
					biggestBlob->setPosition(wPosition);
					biggestBlob->setContours(mContoursApprox);
				}
					
				this->addBlob(biggestBlob);
			}
			else {
				biggestBlob = this->getBlobs()[0];
				{
					biggestBlob->setPosition(wPosition);
					biggestBlob->setContours(mContoursApprox);
				}
			}
		}

		mContours = mContours->h_next;
	}

	cvReleaseImage(&mImageThreshold);
}

void Marker::setColorTolerance(int tolerance) {
	mColorTolerance = tolerance;
}

int Marker::getColorTolerance(void) {
	return mColorTolerance;
}

}}}};