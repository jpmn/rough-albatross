#pragma once

#include "ICaptureService.h"

namespace baluchon { namespace core { namespace services { namespace implementations {

class CameraCaptureService : public ICaptureService
{
public:
	CameraCaptureService(void);
	~CameraCaptureService(void);

	virtual void init(void);
	virtual void initDone(void);
	virtual void execute(void);
	virtual void reset(void);
	virtual void dispose(void);

	virtual void setCapture(CvCapture* capture);
	virtual IplImage* getImage(void);

private:
	CvCapture* mCameraCapture;
	IplImage* mImage;
};

}}}};