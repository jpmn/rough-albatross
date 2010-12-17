#pragma once

#include "IObjectDetectionService.h"
#include "ICaptureService.h"

using namespace baluchon::core::services::capture;

namespace baluchon { namespace core { namespace services { namespace objectdetection {

class ObjectDetectionService : public IObjectDetectionService
{
public:
	ObjectDetectionService(void);
	virtual ~ObjectDetectionService(void);

	virtual void init(void);
	virtual void initDone(void);
	virtual void execute(void);
	virtual void reset(void);
	virtual void dispose(void);

	virtual vector<IDetectable*> getListDetectables(void);
	virtual void addDetector(IDetector* detector);

private:
	ICaptureService* mCaptureService;
	vector<IDetector*> mListDetectors;
	vector<IDetectable*> mListDetectables;
	IplConvKernel* mKernel;
};

}}}};