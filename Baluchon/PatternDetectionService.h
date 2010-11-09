#pragma once
#include "ipatterndetectionservice.h"
#include "ipattern.h"
#include "ICaptureService.h"
#include <vector>

using namespace std;
using namespace baluchon::core::services::capture;

namespace baluchon { namespace core { namespace services { namespace patterndetection { 

class PatternDetectionService :
    public IPatternDetectionService
{
public:
    PatternDetectionService(void);
    ~PatternDetectionService(void);

    void addPattern(IPattern* pattern);
    bool addPattern(char patternName[]);
    vector<IPattern*> getPatterns();

    virtual void init(void);
	virtual void initDone(void);
	virtual void execute(void);
	virtual void reset(void);
	virtual void dispose(void);

private:
    ICaptureService* mCaptureService;
    vector<IPattern*> mPatterns;


    IplImage *mInitial;
    IplImage* mFrame;
    CvMemStorage* mStorage;
    CvSeq* mContours;
    CvSeq* mChildContours;
    CvPoint2D32f mImagePoints[4];
    CvPoint2D32f mModelPoints[4];

    CvSeq* mResult;
    CvMat* mMat;
    CvMat* mSrcPts;
    CvMat* mDstPts;
};

}}}};