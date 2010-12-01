#include "Cube.h"

#include "MathUtility.h"

using namespace baluchon::utilities;

namespace baluchon { namespace core { namespace services { namespace objectdetection {

Cube::Cube(void) {
	
}

Cube::~Cube(void) {

}

Face* Cube::getFaceFront(void) {
	return mFaces[mIndexFront];
}

Face* Cube::getFaceSide(void) {
	return mFaces[mIndexSide];
}

Face* Cube::getFaceUp(void) {
	return mFaces[mIndexUp];
}

void Cube::setFaces(Face* f1, Face* f2, Face* f3) {
	
	mFaces.push_back(f1);
	mFaces.push_back(f2);
	mFaces.push_back(f3);

	std::sort(mFaces.begin(), mFaces.end(), MathUtility::sortByCenterPositionY);

	mIndexUp = 0;

	if (mFaces[1]->getCenterPosition().x < mFaces[2]->getCenterPosition().x) {
		mIndexFront = 1;
		mIndexSide = 2;
	}
	else {
		mIndexFront = 2;
		mIndexSide = 1;
	}
}

}}}};