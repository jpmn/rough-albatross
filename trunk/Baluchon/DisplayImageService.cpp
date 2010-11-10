#include <typeinfo>

#include <highgui.h>

#include "DisplayImageService.h"
#include "IServiceLayer.h"

#include "CameraCaptureService.h"
#include "PatternDetectionService.h"

#include "IPattern.h"

namespace baluchon { namespace core { namespace services { namespace display {

DisplayImageService::DisplayImageService(void) {

}

DisplayImageService::~DisplayImageService(void) {

}

void DisplayImageService::init(void) {
    mCaptureService= new CameraCaptureService();
    mCaptureService = (ICaptureService*) mServiceLayer->findService(mCaptureService);

    mPatternService= new PatternDetectionService();
    mPatternService = (IPatternDetectionService*) mServiceLayer->findService(mPatternService);
}

void DisplayImageService::initDone(void) {
	cvNamedWindow(mWindowName, 1);
}

void DisplayImageService::execute(void) {

    IplImage *initial = mCaptureService->getImage();

    //temporaire...juste pour faire le showoff
    vector<IPattern*> patterns = mPatternService->getPatterns();
    for(int i = 0; i < patterns.size(); i++)
    {
        for(int j = 0; j < (*patterns[i]->getImagePoints()).size(); j++)
        {
            for(int k = 0; k < (*patterns[i]->getImagePoints())[j].size(); k++)
            {
                cvLine(initial, cvPoint((*patterns[i]->getImagePoints())[j][k].x, (*patterns[i]->getImagePoints())[j][k].y), cvPoint((*patterns[i]->getImagePoints())[j][(k+1) % (*patterns[i]->getImagePoints())[j].size()].x, (*patterns[i]->getImagePoints())[j][(k+1) % (*patterns[i]->getImagePoints())[j].size()].y), CV_RGB(255,0,0,0), 5);
            }
        }
    }

	cvShowImage(mWindowName, initial);
}

void DisplayImageService::reset(void) {

}

void DisplayImageService::dispose(void) {
	cvDestroyWindow(mWindowName);
}

void DisplayImageService::setWindowName(char* name) {
	mWindowName = name;
}

}}}};