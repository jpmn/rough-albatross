#pragma once

#include <cv.h>
#include <vector>

#include "IBlob.h"
#include "IColorable.h"

using namespace std;
using namespace baluchon::core::datas;

namespace baluchon { namespace core { namespace services { namespace colordetection {

class IMarker : public IColorable
{
public:
	virtual ~IMarker(void) {}

	virtual void addBlob(IBlob*) = 0;
	virtual vector<IBlob*> getBlobs(void) = 0;
	virtual void clearBlobs(void) = 0;
};

}}}};