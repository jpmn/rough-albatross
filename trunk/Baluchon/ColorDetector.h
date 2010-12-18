#pragma once

#include <cv.h>

#include "IDetector.h"
#include "MarkerFactory.h"

using namespace baluchon::core::datas::detection;

namespace baluchon { namespace core { namespace services { namespace colordetection {

class ColorDetector : public IDetector
{
public:
	ColorDetector(void);
	virtual ~ColorDetector(void);

	vector<IDetectable*> find(IplImage* img, IplImage* src);

	void addColor(CvScalar color, int tolerance);

	void setMaxMarkerCount(int count);
	int getMaxMarkerCount(void);

	void setMinimumSize(int size);
	int getMinimumSize(void);

private:
	IplImage* mImageThreshold;
	IplConvKernel* mMorphKernel;
	CvMemStorage* mStorage;
	CvSeq* mContours;
	CvSeq* mContoursApprox;
	CvSeq* mContoursBiggest;

	vector<CvScalar> mListColors;
	vector<int> mListColorsTolerance;

	MarkerFactory* mMarkerFactory;
	int mMaxMarkerCount;
	int mMinimumSize;
};

}}}};