#pragma once

#include "IWriterService.h"
#include "IDisplayService.h"

using namespace baluchon::core::services::display;
using namespace baluchon::core::services::writer;

namespace baluchon { namespace core { namespace services { namespace writer {

class VideoWriterService : public IWriterService
{
public:
	VideoWriterService(void);
	~VideoWriterService(void);

	virtual void init(void);
	virtual void initDone(void);
	virtual void execute(void);
	virtual void reset(void);
	virtual void dispose(void);

private:
	CvVideoWriter* mVideoWriter;
	IDisplayService* mDisplayService;

};

}}}};