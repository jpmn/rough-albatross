#include "Pattern.h"
#include "cv.h"
#include "highgui.h"

namespace baluchon { namespace core { namespace services { namespace patterndetection { 

Pattern::Pattern(char path[])
{
    mPath = path;
    mWidth = 0;
    mHeight = 0;
    mPointCount = 0;

    mImgPoints = new vector<vector<CvPoint2D32f>>();
    mFramePoints = new vector<vector<CvPoint2D32f>>();
    mOrientations = new vector<int>();

    init();
}


Pattern::~Pattern(void)
{
}

void Pattern::init()
{
    IplImage *initial = cvLoadImage(mPath);
    IplImage *img;
    mWidth = initial->width;
    mHeight = initial->height;

    img = cvCreateImage(cvGetSize(initial), initial->depth, 1);
    cvCvtColor(initial, img, CV_BGR2GRAY);
    cvThreshold(img, img, 100, 255, CV_THRESH_BINARY);

    CvMemStorage* g_storage = cvCreateMemStorage(0);

    CvSeq *contours, *result, *patCtr;

    cvFindContours(img, g_storage, &contours, sizeof(CvContour), CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));
    
    int lowX = mWidth;
    int lowY = mHeight;

    while(contours != NULL)
    {
        result = cvApproxPoly(contours, sizeof(CvContour), g_storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0);
        if(cvCheckContourConvexity(result) && fabs(cvContourArea(result, CV_WHOLE_SEQ)) >= (200) && result->total == 4 && contours->v_next != 0 && contours->v_next->h_next == 0) { 

            for(int i = 0; i < 4; i++)
            {
                if((*((CvPoint*) cvGetSeqElem(result, i))).x < lowX)
                {
                    lowX = (*((CvPoint*) cvGetSeqElem(result, i))).x;
                }

                if((*((CvPoint*) cvGetSeqElem(result, i))).y < lowY)
                {
                    lowY = (*((CvPoint*) cvGetSeqElem(result, i))).y;
                }
            }
            mWidth = mWidth - 2*lowX;
            mHeight = mHeight - 2*lowY;

            patCtr = contours->v_next;
            result = cvApproxPoly(patCtr, sizeof(CvContour), g_storage, CV_POLY_APPROX_DP, cvContourPerimeter(patCtr)*0.02, 0);
            
            mPointCount = result->total;
            mSrcPoints = new CvPoint2D32f[mPointCount][4];

            for(int i = 0; i < mPointCount; i++)
            {
                mSrcPoints[i][0].x = (float) (*((CvPoint*) cvGetSeqElem(result, i))).x - lowX;
                mSrcPoints[i][0].y = (float) (*((CvPoint*) cvGetSeqElem(result, i))).y - lowY;

                for(int j = 1; j < 4; j++)
                {
                    mSrcPoints[i][j].x = -1 * mSrcPoints[i][j-1].y + mWidth;
                    mSrcPoints[i][j].y = mSrcPoints[i][j-1].x;
                }
            }
        }
        contours = contours->h_next;
    }

    cvReleaseMemStorage(&g_storage);
    cvReleaseImage(&img);
    cvReleaseImage(&initial);
}

int Pattern::getWidth()
{
    return mWidth;
}

int Pattern::getPointCount()
{
    return mPointCount;
}

int Pattern::getHeight()
{
    return mHeight;
}

CvPoint2D32f Pattern::getSourcePointAt(int pos, int orientation)
{
    return mSrcPoints[pos][orientation];
}

vector<vector<CvPoint2D32f>>* Pattern::getImagePoints()
{
    return mImgPoints;
}

vector<vector<CvPoint2D32f>>* Pattern::getImageFramePoints()
{
    return mFramePoints;
}

vector<int>* Pattern::getImageOrientations()
{
    return mOrientations;
}

}}}};