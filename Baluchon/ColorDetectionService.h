#pragma once

#include "ICaptureService.h"
#include "IColorDetectionService.h"

using namespace baluchon::core::services::capture;

namespace baluchon { namespace core { namespace services { namespace colordetection {

class ColorDetectionService : public IColorDetectionService
{
public:
	ColorDetectionService(void);
	~ColorDetectionService(void);

	virtual void init(void);
	virtual void initDone(void);
	virtual void execute(void);
	virtual void reset(void);
	virtual void dispose(void);

	virtual void addMarker(IMarker* marker);
	virtual vector<IMarker*> getMarkers(void);

	virtual void setColorTolerance(int tolerance);
	virtual int getColorTolerance(void);

	virtual void setMaxMarkerCount(int count);
	virtual int getMaxMarkerCount(void);

private:
	ICaptureService* mCaptureService;
	CvMemStorage* mStorage;
	IplConvKernel* mMorphKernel;
	IplImage* mImageHSV;
	IplImage* mImageThreshold;

	vector<IMarker*> mMarkers;
	int mColorTolerance;
	int mMaxMarkerCount;
};

}}}};