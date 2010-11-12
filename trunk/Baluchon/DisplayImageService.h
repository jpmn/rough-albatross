#pragma once

#include "IDisplayService.h"
#include "ICaptureService.h"
#include "IColorDetectionService.h"
#include "IPatternDetectionService.h"

using namespace baluchon::core::services::capture;
using namespace baluchon::core::services::colordetection;
using namespace baluchon::core::services::patterndetection;

namespace baluchon { namespace core { namespace services { namespace display {

class DisplayImageService : public IDisplayService
{
public:
	static void onMouseClick(int event, int x, int y, int flags, void* param);

public:
	DisplayImageService(void);
	~DisplayImageService(void);

	virtual void init(void);
	virtual void initDone(void);
	virtual void execute(void);
	virtual void reset(void);
	virtual void dispose(void);

	virtual void setWindowName(char* name);
	virtual IplImage* getImage();

private:
	ICaptureService* mCaptureService;
	IColorDetectionService* mMarkerService;
    IPatternDetectionService* mPatternService;

	char* mWindowName;
	IplImage* mImage;
};

}}}};