#pragma once

#include <cv.h>
#include <highgui.h>

#include "IService.h"

namespace Baluchon { namespace Core { namespace Services {

class CVideoWriterService : implements IService
{
public:
	CVideoWriterService(void);
	~CVideoWriterService(void);

	void execute(IplImage* img);
	void initialize(void);
	void initializeDone(void);
	void reset(void);

private:
	CvVideoWriter* mWriter;
};

}}};