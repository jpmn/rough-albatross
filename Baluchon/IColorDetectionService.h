#pragma once

#include "IDetectionService.h"
#include "IMarker.h"

using namespace baluchon::core::datas::detection;

namespace baluchon { namespace core { namespace services { namespace colordetection { 

class IColorDetectionService : public IDetectionService
{
public:
	virtual ~IColorDetectionService() {}
};

}}}};