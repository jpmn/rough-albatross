#pragma once

#include "IMarker.h"

namespace baluchon { namespace core { namespace services { namespace colordetection {

class Marker : public IMarker
{
public:
	Marker(void);
	~Marker(void);

	virtual void addBlob(IBlob*);
	virtual vector<IBlob*> getBlobs(void);
	virtual void clearBlobs(void);
	virtual void findBlobs(IplImage* img);

	virtual void setColorTolerance(int tolerance);
	virtual int getColorTolerance(void);

private:
	CvMemStorage* mStorage;
	IplConvKernel* mMorphKernel;
	IplImage* mImageThreshold;
	CvSeq* mContours;
	CvSeq* mContoursApprox;

	vector<IBlob*> mBlobs;
	int mColorTolerance;
};

}}}};