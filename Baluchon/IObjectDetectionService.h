#pragma once

#include "IService.h"

namespace baluchon { namespace core { namespace services { namespace objectdetection {

class IObjectDetectionService : public IService
{
public:
	virtual ~IObjectDetectionService(void) {}

	virtual void setCornerTolerance(int tolerance) = 0;
};

}}}};