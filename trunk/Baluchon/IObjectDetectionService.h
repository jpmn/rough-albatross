#pragma once

#include <vector>
#include "IDetectionService.h"
#include "IDetectable.h"
#include "IDetector.h"
#include "BoxPrism.h"

using namespace std;
using namespace baluchon::core::datas::detection;

namespace baluchon { namespace core { namespace services { namespace objectdetection {

class IObjectDetectionService : public IDetectionService
{
public:
	virtual ~IObjectDetectionService(void) {}
};

}}}};