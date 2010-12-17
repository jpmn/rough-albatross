#pragma once

#include <cv.h>
#include <vector>

#include "IDetectable.h"

using namespace std;
using namespace baluchon::core::datas;

namespace baluchon { namespace core { namespace services { namespace objectdetection {

class IDetector 
{
public:
	virtual ~IDetector() {}

	virtual vector<IDetectable*> find(IplImage* img, IplImage* src) = 0;
};

}}}};