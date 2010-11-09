#pragma once

#include "IColorDetectionService.h"

namespace baluchon { namespace core { namespace services { namespace colordetection {

class ColorDetectionService : public IColorDetectionService
{
public:
	ColorDetectionService(void);
	~ColorDetectionService(void);

	virtual void init(void);
	virtual void initDone(void);
	virtual void execute(void);
	virtual void reset(void);
	virtual void dispose(void);
};

}}}};