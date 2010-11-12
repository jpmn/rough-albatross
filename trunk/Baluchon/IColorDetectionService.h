#pragma once

#include <cv.h>

#include "IService.h"
#include "IServiceLayer.h"
#include "IMarker.h"

namespace baluchon { namespace core { namespace services { namespace colordetection { 

class IColorDetectionService : public IService
{
public:
	virtual ~IColorDetectionService() {}

	virtual void addMarker(IMarker* marker) = 0;
	virtual vector<IMarker*> getMarkers(void) = 0;

	virtual void setColorTolerance(int tolerance) = 0;
	virtual int getColorTolerance(void) = 0;

	virtual void setMaxMarkerCount(int count) = 0;
	virtual int getMaxMarkerCount(void) = 0;
};

}}}};