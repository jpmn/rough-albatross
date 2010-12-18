#pragma once

#include "ICaptureService.h"
#include "IColorDetectionService.h"

using namespace baluchon::core::services::capture;

namespace baluchon { namespace core { namespace services { namespace colordetection {

class ColorDetectionService : public IColorDetectionService
{
public:
	ColorDetectionService(void);
	virtual ~ColorDetectionService(void);

	void init(void);
	void initDone(void);
	void execute(void);
	void reset(void);
	void dispose(void);

private:
	ICaptureService* mCaptureService;
	IplImage* mImageHSV;
};

}}}};