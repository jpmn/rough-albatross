#pragma once

#include <cv.h>
#include <vector>

#include "IDetectable.h"

using namespace std;

namespace baluchon { namespace core { namespace datas { namespace detection {

class IDetector 
{
public:
	virtual ~IDetector() {}

	virtual vector<IDetectable*> find(IplImage* img, IplImage* src) = 0;
};

}}}};