#include <cv.h>
#include <highgui.h>

#include <time.h>

#include "Engine.h"

using namespace Baluchon::Core::Services;

namespace Baluchon { namespace Core { namespace Engine {

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
	for (unsigned int i = 0; i < mListProcessingServices.size(); i++) 
		mListProcessingServices.at(i)->initialize();

	for (unsigned int i = 0; i < mListProcessingServices.size(); i++)
		mListProcessingServices.at(i)->initializeDone();

	for (unsigned int i = 0; i < mListRenderingServices.size(); i++) 
		mListRenderingServices.at(i)->initialize();

	for (unsigned int i = 0; i < mListRenderingServices.size(); i++)
		mListRenderingServices.at(i)->initializeDone();
}

void CEngine::cycle(void) {
	CvCapture* capture = cvCreateCameraCapture(0);
	//cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 320);
	//cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 240);

	IplImage* imgIn = cvQueryFrame(capture);
	IplImage* imgOut = cvCreateImage(cvGetSize(imgIn), IPL_DEPTH_8U, 3);
	IplImage* imgFinal = 0;

	char exitKey = 0;

	while (exitKey != CEngine::mExitKey) {
		clock_t start = clock();

		imgIn = cvQueryFrame(capture);

		cvFlip(imgIn, imgIn, 1);
		imgFinal = cvCloneImage(imgIn);

		for (unsigned int i = 0; i < mListProcessingServices.size(); i++) {
			mListProcessingServices[i]->execute(imgIn, imgOut);

			cvAdd(imgOut, imgFinal, imgFinal);
			cvZero(imgOut);
		}

		for (unsigned int i = 0; i < mListRenderingServices.size(); i++) {
			mListRenderingServices[i]->execute(imgFinal);
		}
		mCycleCount++;

		mNamedWindow->setImage(imgFinal);
		mNamedWindow->show();

		cvReleaseImage(&imgFinal);

		exitKey = cvWaitKey(10);

		clock_t elapsed = clock() - start;
        long int timeMs = ((float)elapsed) / ((float)CLOCKS_PER_SEC) * 1000.0f;
		printf("Engine::FPS %f\n", 1000.0f / timeMs);
	}

	cvReleaseImage(&imgOut);
	cvReleaseCapture(&capture);
}

void CEngine::dispose(void) {

}

void CEngine::registerServiceForProcessing(IProcessingService* s) {
	mListProcessingServices.push_back(s);
}

void CEngine::registerServiceForRendering(IRenderingService* s) {
	mListRenderingServices.push_back(s);
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

}}};