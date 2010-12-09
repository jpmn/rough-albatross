#include "PoseEstimationService.h"
#include "PatternDetectionService.h"
#include "CameraCaptureService.h"
#include "IServiceLayer.h"
#include "PoseEstimatedPattern.h"

namespace baluchon { namespace core { namespace services { namespace poseestimation { 

PoseEstimationService::PoseEstimationService(char* intrinsicPath, char* distortionPath)
{
    mIntrinsicPath = intrinsicPath;
    mDistortionPath = distortionPath;
}

PoseEstimationService::~PoseEstimationService(void)
{
}

void PoseEstimationService::init(void) {
    mPatternDetectionService = new PatternDetectionService();
    mPatternDetectionService = (IPatternDetectionService*) mServiceLayer->findService(mPatternDetectionService);

    mCaptureService= new CameraCaptureService();
    mCaptureService = (ICaptureService*) mServiceLayer->findService(mCaptureService);

    mIntrinsic = 0;
    mDistortion = 0;

    if(mIntrinsicPath != 0 && mDistortionPath != 0)
    {
        mIntrinsic = (CvMat*)cvLoad(mIntrinsicPath);
        mDistortion = (CvMat*)cvLoad(mDistortionPath);
    }

    for(unsigned int i = 0; i < mPatternDetectionService->getPatterns().size(); i++)
    {
        mPatterns.push_back(new PoseEstimatedPattern(mPatternDetectionService->getPatterns()[i]));
    }
    mPatternDetectionService->getPatterns();
}

void PoseEstimationService::initDone(void) {

}

void PoseEstimationService::execute(void) {

    for(unsigned int i = 0; i < mPatterns.size(); i++)
    {
        mPatterns[i]->getTranslationMatrices()->clear();
        mPatterns[i]->getRotationMatrices()->clear();
    }

    IplImage* img = mCaptureService->getImage();
    for(unsigned int i = 0; i < mPatterns.size(); i++)
    {
        for(unsigned int j = 0; j < mPatterns[i]->getImagePoints()->size(); j++)
        {
            CvMat* imagePoints = cvCreateMat((*mPatterns[i]->getImagePoints())[j].size(), 2, CV_32FC1);
            CvMat* objectPoints = cvCreateMat((*mPatterns[i]->getImagePoints())[j].size(), 3, CV_32FC1);
            
            for(int k = 0; k < mPatterns[i]->getPointCount(); k++)
            {
                // orientation is 2 because when first loading the pattern, the y positive is down, and y negative is up
                cvmSet(objectPoints, k, 0, mPatterns[i]->getSourcePointAt(k, 2).x);
                cvmSet(objectPoints, k, 1, mPatterns[i]->getSourcePointAt(k, 2).y);
                cvmSet(objectPoints, k, 2, 0.0);

                cvmSet(imagePoints, k, 0, (*mPatterns[i]->getImagePoints())[j][k].x);
                cvmSet(imagePoints, k, 1, (*mPatterns[i]->getImagePoints())[j][k].y);
            }

            if(mIntrinsic == 0)
            {
                CvMat* pointCount = cvCreateMat(1, 1, CV_32SC1);
                mIntrinsic = cvCreateMat( 3, 3, CV_32FC1 );
	            mDistortion = cvCreateMat( 5, 1, CV_32FC1 );

                cvCalibrateCamera2(objectPoints, imagePoints, pointCount, cvGetSize(img), mIntrinsic, mDistortion, NULL, NULL, CV_CALIB_FIX_ASPECT_RATIO);

            }

            CvMat *rotation = cvCreateMat (1, 3, CV_32FC1);
	        CvMat *translation = cvCreateMat (1 , 3, CV_32FC1);
            cvFindExtrinsicCameraParams2(objectPoints, imagePoints, mIntrinsic, mDistortion, rotation, translation);

            mPatterns[i]->getRotationMatrices()->push_back(rotation);
            mPatterns[i]->getTranslationMatrices()->push_back(translation);
        }
    }
}

void PoseEstimationService::reset(void) {

}

void PoseEstimationService::dispose(void) {
}

vector<IPoseEstimatedPattern*> PoseEstimationService::getPatterns()
{
    return mPatterns;
}

}}}};