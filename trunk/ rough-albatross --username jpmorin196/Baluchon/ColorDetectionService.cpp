#include <iostream>

#include <highgui.h>

#include "ColorDetectionService.h"
#include "NamedWindow.h"
#include "ImageWrapper.h"

using namespace Baluchon::Utils;
using namespace Baluchon::Core::Components::Windows;

namespace Baluchon { namespace Core { namespace Services {

CColorDetectionService::CColorDetectionService(void)
{
	mWinThreshold = new CNamedWindow();
	{
		mWinThreshold->setName("Threshold");
		mWinThreshold->setFlag(CV_WINDOW_AUTOSIZE);
	}

	mColorTolerance = 0;

	mMorphKernel = cvCreateStructuringElementEx(5, 5, 1, 1, CV_SHAPE_RECT, NULL);
	
	cvSetMouseCallback("Camera :: Query Frame", (CvMouseCallback)CColorDetectionService::onMouseClick, (void*)this);

	cvNamedWindow("DEBUG", 1);
}

CColorDetectionService::~CColorDetectionService(void)
{
	delete mWinThreshold;
	cvReleaseStructuringElement(&mMorphKernel);
	cvDestroyWindow("DEBUG");
}

void CColorDetectionService::addColor(CColor color) {
	if (mListColors.size() == mMaxColorCount)
		mListColors.erase(mListColors.begin());

	mListColors.push_back(color);
}

void CColorDetectionService::setColorTolerance(int t) {
	mColorTolerance = t;
}

void CColorDetectionService::setMaxColorCount(int c) {
	mMaxColorCount = c;
}

void CColorDetectionService::execute(const IplImage* imgIn, IplImage* imgOut) {
	//printf("ColorDetectionService\n");

	mLastImage = imgIn;

	//imgOut = cvCreateImage(cvGetSize(imgIn), IPL_DEPTH_8U, 3);
	//cvZero(imgOut);

	IplImage* imgHSV = cvCreateImage(cvGetSize(imgIn), IPL_DEPTH_8U, 3);
	cvCvtColor(imgIn, imgHSV, CV_BGR2HSV);

	// Rend floue l'image pour réduire le bruit (lent)
	//cvSmooth(imgHSV, imgHSV, CV_GAUSSIAN, 5);

	IplImage* imgGray = cvCreateImage(cvGetSize(imgIn), IPL_DEPTH_8U, 1);
	
	int colorListHeight = 10;

	for (int i = 0; i < mListColors.size(); i++) {
		cvZero(imgGray);

		CColor color = mListColors.at(i);

		cvDrawRect(imgOut, cvPoint(10, colorListHeight), cvPoint(25, colorListHeight + 10), color.getRGB(), -1);
		cvDrawRect(imgOut, cvPoint(35, colorListHeight), cvPoint(50, colorListHeight + 10), color.getHSV(), -1);

		colorListHeight += 20;

		int h = color.getHSV().val[0];
		int s = color.getHSV().val[1];
		int v = color.getHSV().val[2];

		// Applique un threshold sur la couleur en tenant compte de la tolérance
		cvInRangeS(imgHSV, cvScalar(h - mColorTolerance, s - mColorTolerance, 0), 
			cvScalar(h + mColorTolerance, s + mColorTolerance, 255), imgGray);

		// Applique un dilate et erode pour éliminer le bruit
		cvMorphologyEx(imgGray, imgGray, NULL, mMorphKernel, CV_MOP_OPEN, 1);
		
		cvShowImage("DEBUG", imgHSV);

		CvMemStorage* storage = cvCreateMemStorage(0);
		CvSeq* contour = 0;

		// Trouve les contours dans l'image en niveaux de gris retournée par le threshold
		cvFindContours(imgGray, storage, &contour, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

		CvPoint wPosition = cvPoint(0, 0);
		CvMoments moments;

		int cpt = 0;
		while (contour != 0) {
			double wContourAreaSize = cvContourArea(contour, CV_WHOLE_SEQ);

			// Conserve seulement les contours d'une taille satisfaisante
			if (wContourAreaSize > 50) {
				cvDrawContours(imgOut, contour, color.getRGB(), color.getRGB(), -1, CV_FILLED, 8);

				cvContourMoments(contour, &moments); 

				wPosition.x += moments.m10/moments.m00;
				wPosition.y += moments.m01/moments.m00;
				
				cpt++;
			}
			contour = contour->h_next;
		}

		if (cpt > 0) {
			wPosition.x /= cpt;
			wPosition.y /= cpt;

			cvDrawCircle(imgOut, cvPoint(wPosition.x, wPosition.y), 5, CV_RGB(0, 255, 0), -1, 8);
		}

		cvReleaseMemStorage(&storage);
	}

	mWinThreshold->setImage(imgOut);
	mWinThreshold->show();

	cvReleaseImage(&imgGray);
	cvReleaseImage(&imgHSV);
}

void CColorDetectionService::initialize(void) {

}

void CColorDetectionService::initializeDone(void) {

}

void CColorDetectionService::reset(void) {

}

const IplImage* CColorDetectionService::getLastImage(void) {
	return mLastImage;
}

void CColorDetectionService::onMouseClick(int event, int x, int y, int flags, void* param = NULL) {
	if (event == CV_EVENT_LBUTTONUP) {
		CColorDetectionService* wColorService = (CColorDetectionService*)param;
		const IplImage* img = wColorService->getLastImage();

		IplImage* hsv = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);
		cvCvtColor(img, hsv, CV_BGR2HSV);

		CColor* wColor = new CColor();

		CvScalar c = cvGet2D(img, y, x);
		wColor->setRGB(c);
		c = cvGet2D(hsv, y, x);
		wColor->setHSV(c);

		wColorService->addColor(*wColor);

		cvReleaseImage(&hsv);
	}
}

}}};
