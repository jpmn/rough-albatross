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

		CvScalar colorMarkerHSV = mMarkers[i]->getColor();//ColorUtility::convertColorBGRtoHSV(mMarkers[i]->getColor());

		// Applique un threshold sur la couleur en tenant compte de la tolérance
		cvInRangeS(
			mImageHSV, 
			cvScalar(colorMarkerHSV.val[0] - mColorTolerance, colorMarkerHSV.val[1] - mColorTolerance, 0),
			cvScalar(colorMarkerHSV.val[0] + mColorTolerance, colorMarkerHSV.val[1] + mColorTolerance, 255),
			mImageThreshold
		);

		// Applique un dilate et erode pour éliminer le bruit
		cvMorphologyEx(mImageThreshold, mImageThreshold, NULL, mMorphKernel, CV_MOP_OPEN, 1);

		//cvCanny(mImageThreshold, mImageThreshold, 0, 10, 5);

		cvShowImage("Canny", mImageThreshold);
		cvShowImage("HSV", mImageHSV);

		mContours = 0;
		mContoursApprox = 0;
		cvClearMemStorage(mStorage);

		// Trouve les contours dans l'image en niveaux de gris retournée par le threshold
		cvFindContours(mImageThreshold, mStorage, &mContours, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

		cvZero(mImageThreshold);

		while (mContours != NULL) {
			mContoursApprox = cvApproxPoly(mContours, sizeof(CvContour), mStorage, CV_POLY_APPROX_DP, cvContourPerimeter(mContours)*0.02, 0);

			double wContourAreaSize = fabs(cvContourArea(mContoursApprox, CV_WHOLE_SEQ));

			if (wContourAreaSize > 250.0f) {
				CvPoint wPosition = cvPoint(0, 0);
				CvMoments moments;

				cvContourMoments(mContoursApprox, &moments); 

				wPosition.x = moments.m10 / moments.m00;
				wPosition.y = moments.m01 / moments.m00;

				/*
				CvSeq* mContoursMerge = mContours->h_prev;

				while (mContoursMerge != NULL) {
					CvPoint pos = cvPoint(0, 0);

					cvContourMoments(mContoursMerge, &moments); 

					pos.x = moments.m10 / moments.m00;
					pos.y = moments.m01 / moments.m00;

					cvDrawCircle(imgIn, pos, 5, CV_RGB(0, 0, 255), 3, 8); 

					mContoursMerge = mContoursMerge->h_next;
				}
				*/
				bool merged = false;
				/*
				vector<IBlob*> blobs = mMarkers[i]->getBlobs();
				for (unsigned int j = 0; j < blobs.size(); j++) {
					CvPoint blobPosition = blobs[j]->getPosition();

					double distance = sqrt(pow((double)blobPosition.x - wPosition.x, 2) + pow((double)blobPosition.y - wPosition.y, 2));

					printf("DISTANCE: %f\n", distance);

					if (distance < 60) {
						while (mContoursApprox != NULL) {
							cvSeqPush(blobs[j]->getContours(), mContoursApprox);
							mContoursApprox = mContoursApprox->h_next;
						}
						merged = true;
					}
				}
				*/
				if (!merged) {
					IBlob* blob = new Blob();
					{
						blob->setPosition(wPosition);
						blob->setContours(mContoursApprox);
					}

					mMarkers[i]->addBlob(blob);
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