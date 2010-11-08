#pragma once

#include "IColorDetectionService.h"

namespace baluchon { namespace core { namespace services { namespace implementations {

class ColorDetectionService : public IColorDetectionService
{
public:
	ColorDetectionService(void);
	~ColorDetectionService(void);
};

}}}};