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
	mKernel = cvCreateStructuringElementEx(5, 5, 2, 2, CV_SHAPE_ELLIPSE);

	mWinColors = new CNamedWindow();
	{
		mWinColors->setName("Colors");
		mWinColors->setFlag(CV_WINDOW_AUTOSIZE);
	}

	mWinThreshold = new CNamedWindow();
	{
		mWinThreshold->setName("Threshold");
		mWinThreshold->setFlag(CV_WINDOW_AUTOSIZE);
	}

	mColorTolerance = 0;

	cvSetMouseCallback("Camera :: Query Frame", (CvMouseCallback)CColorDetectionService::onMouseClick, (void*)this);
}

CColorDetectionService::~CColorDetectionService(void)
{
	cvReleaseStructuringElement(&mKernel);
	delete mWinColors;
	delete mWinThreshold;
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

	IplImage* imgHSV = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
	cvCvtColor(img, imgHSV, CV_BGR2HSV);
	cvSmooth(imgHSV, imgHSV, CV_GAUSSIAN);

	IplImage* imgColors = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);

	IplImage* imgThreshold = cvCreateImage(cvGetSize(imgHSV), IPL_DEPTH_8U, 1);

	RgbImage wImgColors(imgColors);
	BwImage wImgThreshold(imgThreshold);

	for (int i = 0; i < mListColors.size(); i++) {
		CColor color = mListColors.at(i);
		cvZero(imgThreshold);

		int h = color.getHSV().val[0], s = color.getHSV().val[1], v = color.getHSV().val[2], t = mColorTolerance;

		cvInRangeS(imgHSV, cvScalar(h-t-1, s-t, 0), cvScalar(h+t-1, s+t, 255), imgThreshold);
		
		cvDilate(imgThreshold, imgThreshold, mKernel, 5);
		cvErode(imgThreshold, imgThreshold, mKernel, 5);

		for (int y = 0; y < imgColors->height; y++) {
			for (int x = 0; x < imgColors->width; x++) {

				if (wImgThreshold[y][x] == 255) { // blanc
					wImgColors[y][x].b = color.getRGB().val[0];
					wImgColors[y][x].g = color.getRGB().val[1];
					wImgColors[y][x].r = color.getRGB().val[2];
				}
			}
		}
	}

	mWinColors->setImage(imgColors);
	mWinColors->show();

	//mWinThreshold->setImage(imgThreshold);
	//mWinThreshold->show();

	cvReleaseImage(&imgThreshold);
	cvReleaseImage(&imgColors);
	cvReleaseImage(&imgHSV);
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
