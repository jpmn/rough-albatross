#include "Marker.h"

namespace baluchon { namespace core { namespace services { namespace colordetection {

Marker::Marker(void) {

}

Marker::~Marker(void) {
	clearBlobs();
}

void Marker::addBlob(IBlob* blob) {
	mBlobs.push_back(blob);
}

vector<IBlob*> Marker::getBlobs(void) {
	return mBlobs;
}

void Marker::clearBlobs(void) {
	for (unsigned int i = 0; i < mBlobs.size(); i++) {
		delete mBlobs[i];
	}
	mBlobs.clear();
}

}}}};