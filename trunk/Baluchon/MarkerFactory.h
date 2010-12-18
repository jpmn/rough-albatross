#pragma once

#include <cv.h>

#include "ColoredMarker.h"

using namespace baluchon::core::datas::detection;

namespace baluchon { namespace core { namespace services { namespace colordetection {

class MarkerFactory
{
public:
	MarkerFactory(void);
	~MarkerFactory(void);

	ColoredMarker* createColoredMarker(CvSeq* contours, CvScalar color, int tolerance);
};

}}}};