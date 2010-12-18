#pragma once

#include <cv.h>
#include <vector>

#include "IBlob.h"
#include "IColorable.h"

using namespace std;

namespace baluchon { namespace core { namespace datas { namespace detection {

class IMarker
{
public:
	virtual ~IMarker(void) {}
};

}}}};