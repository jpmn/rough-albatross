#include "PatternDetectionService.h"

#include "Pattern.h"

#include "IServiceLayer.h"
#include "CameraCaptureService.h"
#include "math.h"

namespace baluchon { namespace core { namespace services { namespace patterndetection { 

PatternDetectionService::PatternDetectionService(void)
{
}


PatternDetectionService::~PatternDetectionService(void)
{
}

void PatternDetectionService::addPattern(IPattern* pattern)
{
    mPatterns.push_back(pattern);
}

bool PatternDetectionService::addPattern(char patternName[])
{
    IPattern *pattern = new Pattern(patternName);
    if(pattern != 0)
    {
        mPatterns.push_back(pattern);
        return true;
    }
    return false;
}

vector<IPattern*> PatternDetectionService::getPatterns()
{
    return mPatterns;
}

void PatternDetectionService::init(void) {
    mCaptureService= new CameraCaptureService();
    mCaptureService = (ICaptureService*) mServiceLayer->findService(mCaptureService);

     mStorage = 0;
     mMat = cvCreateMat(3,3,CV_32FC1);
     mModelPoints[0].x = 0;
     mModelPoints[0].y = 0;
     mModelPoints[1].y = 0;
     mModelPoints[3].x = 0;
}

void PatternDetectionService::initDone(void) {

}

void PatternDetectionService::execute(void) {

    for(int i = 0; i < mPatterns.size(); i++)
    {
        mPatterns[i]->getImagePoints()->clear();
    }

    mInitial = mCaptureService->getImage();

    if( !mInitial ) {
        return;
    }

    mFrame = cvCreateImage(cvGetSize(mInitial), mInitial->depth, 1);
    cvCvtColor(mInitial, mFrame, CV_BGR2GRAY);
    cvThreshold(mFrame, mFrame, 100, 255, CV_THRESH_BINARY);

    if(mStorage == 0) {
	    mStorage = cvCreateMemStorage(0);
	} else {
	    cvClearMemStorage(mStorage);
    }

	mContours = 0;
    mResult = 0;

    cvFindContours(mFrame, mStorage, &mContours, sizeof(CvContour), CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));
    
    cvZero(mFrame);

    while(mContours != 0)
    {
        //Approximates polygonal curves with desired precision
        mResult = cvApproxPoly(mContours, sizeof(CvContour), mStorage, CV_POLY_APPROX_DP, cvContourPerimeter(mContours)*0.02, 0);

        //if contour is convex, and area is big enough, and number of vertices is exactly 4, and has at least one child connected component, its GOOD
        if(cvCheckContourConvexity(mResult) && fabs(cvContourArea(mResult, CV_WHOLE_SEQ)) >= (200) && mResult->total == 4 && mContours->v_next != 0) {

            //only one child should be connected
            if(mContours->v_next->h_next == 0)
            {

                for(int j = 0; j < 4; j++)
                {
                    mImagePoints[j].x = (float) ((CvPoint*) cvGetSeqElem(mResult, j))->x;
                    mImagePoints[j].y = (float) ((CvPoint*) cvGetSeqElem(mResult, j))->y;
                }

                //Child connected component
                mChildContours = mContours->v_next;
                mResult = cvApproxPoly(mChildContours, sizeof(CvContour), mStorage, CV_POLY_APPROX_DP, cvContourPerimeter(mChildContours)*0.02, 0);
                         
                mSrcPts = cvCreateMat(1,mResult->total,CV_32FC2);
                mDstPts = cvCreateMat(1,mResult->total,CV_32FC2);

                for(int i = 0; i < mResult->total; i++)
                {
                    mSrcPts->data.fl[i*2] = (float) (*((CvPoint*) cvGetSeqElem(mResult, i))).x;
                    mSrcPts->data.fl[i*2+1] = (float) (*((CvPoint*) cvGetSeqElem(mResult, i))).y;
                }

                mModelPoints[1].x = 0;
                mModelPoints[2].x = 0;
                mModelPoints[2].y = 0;
                mModelPoints[3].y = 0;

                for(int i = 0; i < mPatterns.size(); i++)
                {
                    if(mResult->total == mPatterns[i]->getPointCount())
                    {
                        //optimization: if the size of the new pattern is more than 2% of the last one, we recalculate the transform
                        if(mModelPoints[1].x == 0 || fabs(((float) (mPatterns[i]->getWidth() - mPatterns[i-1]->getWidth()))/((float) mPatterns[i]->getWidth())) + fabs(((float) (mPatterns[i]->getHeight() - mPatterns[i-1]->getHeight()))/((float) mPatterns[i]->getHeight())) > 0.02)
                        {
                            mModelPoints[1].x = (float) mPatterns[i]->getWidth();
                            mModelPoints[2].x = (float) mPatterns[i]->getWidth();
                            mModelPoints[2].y = (float) mPatterns[i]->getHeight();
                            mModelPoints[3].y = (float) mPatterns[i]->getHeight();

                            cvGetPerspectiveTransform(mImagePoints, mModelPoints, mMat);
                            cvPerspectiveTransform(mSrcPts, mDstPts, mMat);
                        }

                        // pattern validity check
                        bool valid = false;
                        int j = 0;
                        int k;
                        int l;

                        while(j < 4 && !valid)
                        {
                            k = 0;
                            while(k < mResult->total && !valid)
                            {
                                l = 0;
                                valid = true;
                                while(l < mResult->total && valid)
                                {
                                    // 30 pixels threshold value. TODO: SETTABLE
                                    if(sqrtf(pow(mDstPts->data.fl[((k-l+mResult->total) % mResult->total)*2] - mPatterns[i]->getSourcePointAt(l, j).x, 2) + pow(mDstPts->data.fl[((k-l+mResult->total) % mResult->total)*2+1] - mPatterns[i]->getSourcePointAt(l, j).y, 2)) > 30)
                                    {
                                        valid = false;
                                    }

                                    l++;
                                }

                                k++;
                            }

                            j++;
                        }


                        if(valid)
                        {
                            vector<CvPoint2D32f> tempPoints;

                            for(int j = 0; j < mResult->total; j++)
                            {
                                tempPoints.push_back(cvPoint2D32f((*((CvPoint*) cvGetSeqElem(mResult, j))).x, (*((CvPoint*) cvGetSeqElem(mResult, j))).y));
                            }
                            mPatterns[i]->getImagePoints()->push_back(tempPoints);
                        }
                    }
                }

                cvReleaseData(mSrcPts);
                cvReleaseData(mDstPts);
            }
        }


        mContours = mContours->h_next;
    }

    if(mFrame != 0) {
        cvReleaseImage(&mFrame);
    }
}

void PatternDetectionService::reset(void) {

}

void PatternDetectionService::dispose(void) {
}

}}}};
