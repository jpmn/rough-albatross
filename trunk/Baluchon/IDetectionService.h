#pragma once

#include <vector>

#include "IService.h"
#include "IDetectable.h"
#include "IDetector.h"

using namespace std;
using namespace baluchon::core::datas::detection;

namespace baluchon { namespace core { namespace services {

class IDetectionService : public IService
{
public:
	virtual ~IDetectionService() {}

	void addDetector(IDetector* detector) {
		mListDetectors.push_back(detector);
	}

	vector<IDetectable*> getDetectables() {
		return mListDetectables;
	}	
    
protected:
	vector<IDetector*> mListDetectors;
	vector<IDetectable*> mListDetectables;
};

}}};