#include "Blob.h"

namespace baluchon {  namespace core { namespace services { namespace colordetection {

Blob::Blob(void) {

}

Blob::~Blob(void) {
	delete mContour;
}

}}}};