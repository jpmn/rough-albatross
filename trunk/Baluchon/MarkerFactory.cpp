#include "MarkerFactory.h"

namespace baluchon { namespace core { namespace services { namespace colordetection {

MarkerFactory::MarkerFactory(void) {

}

MarkerFactory::~MarkerFactory(void) {

}

ColoredMarker* MarkerFactory::createColoredMarker(CvSeq* contours, CvScalar color, int tolerance) {

	ColoredMarker* marker = new ColoredMarker();
	{
		marker->setContours(contours);
		marker->setColor(color);
		marker->setTolerance(tolerance);
	}

	return marker;
}

}}}};