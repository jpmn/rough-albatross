#pragma once

#include <cv.h>
#include <highgui.h>

#include "IRenderingService.h"

namespace Baluchon { namespace Core { namespace Services {

class CVideoWriterService : implements IRenderingService
{
public:
	CVideoWriterService(void);
	~CVideoWriterService(void);

	void execute(const IplImage* imgIn, IplImage* imgOut);
	void initialize(void);
	void initializeDone(void);
	void reset(void);

private:
	CvVideoWriter* mWriter;
};

}}};