#pragma once

#include "IDisplayService.h"
#include "ICaptureService.h"
#include "IColorDetectionService.h"
#include "IPatternDetectionService.h"
#include "IPoseEstimationService.h"

using namespace baluchon::core::services::capture;
using namespace baluchon::core::services::colordetection;
using namespace baluchon::core::services::patterndetection;
using namespace baluchon::core::services::poseestimation;

namespace baluchon { namespace core { namespace services { namespace display {

class DisplayImageService : public IDisplayService
{
public:
	static void onMouseClick(int event, int x, int y, int flags, void* param);

public:
	DisplayImageService(void);
	virtual ~DisplayImageService(void);

	void init(void);
	void initDone(void);
	void execute(void);
	void reset(void);
	void dispose(void);

	void setWindowName(char* name);
	IplImage* getImage();

private:
	ICaptureService* mCaptureService;
	IColorDetectionService* mColorDetectionService;

	char* mWindowName;
	IplImage* mImage;
};

}}}};