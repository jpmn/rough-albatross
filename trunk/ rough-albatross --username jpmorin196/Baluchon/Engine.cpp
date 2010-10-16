#include <cv.h>
#include <highgui.h>

#include "Engine.h"

using namespace Baluchon::Core::Services;

namespace Baluchon { namespace Core {

CEngine::CEngine(void)
{
	mNamedWindow = 0;
	mCycleCount = 0;
	mExitKey = 0;
	mCycleDuration = 50;
}

CEngine::~CEngine(void)
{
	
}

void CEngine::init(void) {
	printf("Engine::init\n");
}

void CEngine::cycle(void) {
	mNamedWindow->init();

	CvCapture* capture = cvCreateCameraCapture(0);
	IplImage* imgFrame = 0;

	char exitKey = 0;
	double t = cvGetTickCount();
	double time = 0;

	while (exitKey != CEngine::mExitKey) {
		imgFrame = cvQueryFrame(capture);

		cvFlip(imgFrame, imgFrame, 1);

		printf("Engine::cycle %d\n", mCycleCount);
		for (unsigned int i = 0; i < mListServices.size(); i++) 
			mListServices[i]->execute();
		mCycleCount++;

		mNamedWindow->setImage(imgFrame);
		mNamedWindow->show();

		exitKey = cvWaitKey(10);

		t = cvGetTickCount() - t;

		do {
			time = (t / cvGetTickFrequency()) * 1000;
			printf("%f\n", time);
		} while (time < mCycleDuration);

		printf("Engine::duration %f\n", time);
	}

	cvReleaseCapture(&capture);
}

void CEngine::dispose(void) {

}

void CEngine::registerService(IService* s) {
	mListServices.push_back(s);
}

void CEngine::setNamedWindow(INamedWindow* nw) {
	mNamedWindow = nw;
}

void CEngine::setExitKey(char key) {
	mExitKey = key;
}

void CEngine::setCycleDuration(int ms) {
	mCycleDuration = ms;
}

}};