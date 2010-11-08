#pragma once

#include "ICaptureService.h"

namespace Baluchon { namespace Core { namespace Services { namespace Implementations {

class CameraCaptureService : implements ICaptureService
{
public:
	CameraCaptureService(void);
	~CameraCaptureService(void);

	virtual void Init(void);
	virtual void InitDone(void);
	virtual void Execute(void);
	virtual void Reset(void);
	virtual void Dispose(void);

	virtual void SetCapture(CvCapture* capture);
	virtual IplImage* GetImage(void);

private:
	CvCapture* mCameraCapture;
	IplImage* mImage;
};

}}}};