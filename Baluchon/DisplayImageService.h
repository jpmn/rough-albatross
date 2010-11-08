#pragma once

#include "IDisplayService.h"
#include "ICaptureService.h"

namespace baluchon { namespace core { namespace services { namespace implementations {

class DisplayImageService : public IDisplayService
{
public:
	DisplayImageService(void);
	~DisplayImageService(void);

	virtual void init(void);
	virtual void initDone(void);
	virtual void execute(void);
	virtual void reset(void);
	virtual void dispose(void);

	virtual void setWindowName(char* name);

private:
	ICaptureService* mCaptureService;
	char* mWindowName;
};

}}}};