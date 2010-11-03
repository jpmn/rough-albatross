#include <iostream>

#include <highgui.h>

#include "ColorDetectionService.h"
#include "NamedWindow.h"
#include "ImageWrapper.h"

using namespace Baluchon::Utils;
using namespace Baluchon::Core::Components;

namespace Baluchon { namespace Core { namespace Services {

CColorDetectionService::CColorDetectionService(void)
{
	mWinThreshold = new CNamedWindow();
	{
		mWinThreshold->setName("Threshold");
		mWinThreshold->setFlag(CV_WINDOW_AUTOSIZE);
	}

	mColorTolerance = 0;

		cvNamedWindow("Patate", 1);

	cvSetMouseCallback("Camera :: Query Frame", (CvMouseCallback)CColorDetectionService::onMouseClick, (void*)this);
}

CColorDetectionService::~CColorDetectionService(void)
{
	delete mWinThreshold;
	cvDestroyWindow("Patate");
}

void CColorDetectionService::addColor(CColor color) {
	mListColors.push_back(color);
}

void CColorDetectionService::setColorTolerance(int t) {
	mColorTolerance = t;
}

void CColorDetectionService::execute(IplImage* img) {
	//printf("ColorDetectionService\n");

	mLastImage = img;

	IplImage* imgOut = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
	IplImage* imgHSV = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
	cvCvtColor(img, imgHSV, CV_BGR2HSV);

	for (int i = 0; i < mListColors.size(); i++) {
	
		IplImage* imgGray = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
		//cvSplit(img, imgGray, 0, 0, 0);

		///
		CColor color = mListColors.at(i);

		int h = color.getHSV().val[0];
		int s = color.getHSV().val[1];

		cvInRangeS(imgHSV, cvScalar(h - mColorTolerance, s - mColorTolerance, 0), cvScalar(h + mColorTolerance, s + mColorTolerance, 255), imgGray);

		///
		CvMemStorage* storage = cvCreateMemStorage(0);
		CvSeq* contour = 0;
	
		cvFindContours(imgGray, storage, &contour, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
		
		while (contour != 0) {
			double wContourAreaSize = cvContourArea(contour, CV_WHOLE_SEQ);

			if (wContourAreaSize > 80)
				cvDrawContours(imgOut, contour, color.getRGB(), color.getRGB(), -1, CV_FILLED, 8);

			contour = contour->h_next;
		}

		cvShowImage("Patate", imgGray);

		cvReleaseImage(&imgGray);
		cvReleaseMemStorage(&storage);
	}

	mWinThreshold->setImage(imgOut);
	mWinThreshold->show();

	cvReleaseImage(&imgHSV);
	cvReleaseImage(&imgOut);
}

void CColorDetectionService::initialize(void) {

}

void CColorDetectionService::initializeDone(void) {

}

void CColorDetectionService::reset(void) {

}

IplImage* CColorDetectionService::getLastImage(void) {
	return mLastImage;
}

void CColorDetectionService::onMouseClick(int event, int x, int y, int flags, void* param = NULL) {
	if (event == CV_EVENT_LBUTTONUP) {
		CColorDetectionService* wColorService = (CColorDetectionService*)param;
		IplImage* img = wColorService->getLastImage();

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
