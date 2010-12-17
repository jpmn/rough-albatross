#pragma once

#include <vector>
#include "IService.h"
#include "IDetectable.h"
#include "IDetector.h"
#include "BoxPrism.h"

using namespace std;
using namespace baluchon::core::datas;

namespace baluchon { namespace core { namespace services { namespace objectdetection {

class IObjectDetectionService : public IService
{
public:
	virtual ~IObjectDetectionService(void) {}

	virtual vector<IDetectable*> getListDetectables(void) = 0;
	virtual void addDetector(IDetector* detector) = 0;
};

}}}};