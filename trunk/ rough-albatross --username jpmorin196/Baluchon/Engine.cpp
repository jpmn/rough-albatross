#include <cv.h>
#include <highgui.h>

#include <time.h>

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
	CvCapture* capture = cvCreateCameraCapture(0);
	IplImage* imgFrame = 0;
	
	char exitKey = 0;

	while (exitKey != CEngine::mExitKey) {
		clock_t start = clock();

		imgFrame = cvQueryFrame(capture);

		cvFlip(imgFrame, imgFrame, 1);

		printf("Engine::cycle %d\n", mCycleCount);
		for (unsigned int i = 0; i < mListServices.size(); i++) 
			mListServices[i]->execute(imgFrame);
		mCycleCount++;

		mNamedWindow->setImage(imgFrame);
		mNamedWindow->show();

		exitKey = cvWaitKey(10);

		clock_t elapsed = clock() - start;
        long int timeMs = ((float)elapsed) / ((float)CLOCKS_PER_SEC) * 1000.0f;
		printf("Engine::FPS %f\n", 1000.0f / timeMs);
	}

	cvReleaseCapture(&capture);
}

void CEngine::dispose(void) {

}

void CEngine::registerService(IService* s) {
	mListServices.push_back(s);
}

void CEngine::unregisterService(IService* s) {

	// TODO : vérifier si ça fonctionne vraiment...
	for (int i = 0; i < mListServices.size(); i++) {
		if (mListServices.at(i) == s) {
			mListServices.erase(mListServices.begin() + i);
			break;
		}
	}
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