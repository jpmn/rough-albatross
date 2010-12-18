#pragma once

#include "IObjectDetectionService.h"
#include "ICaptureService.h"

using namespace baluchon::core::datas::detection;
using namespace baluchon::core::services::capture;

namespace baluchon { namespace core { namespace services { namespace objectdetection {

class ObjectDetectionService : public IObjectDetectionService
{
public:
	ObjectDetectionService(void);
	virtual ~ObjectDetectionService(void);

	void init(void);
	void initDone(void);
	void execute(void);
	void reset(void);
	void dispose(void);

private:
	ICaptureService* mCaptureService;
	IplImage* mImageHSV;
	IplImage* mImageGray;
	IplImage* mImageContours;
	IplConvKernel* mMorphKernel;
};

}}}};