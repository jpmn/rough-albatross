#pragma once

#include "Face.h"

namespace baluchon { namespace core { namespace services { namespace objectdetection {

class Cube
{
public:
	Cube(void);
	~Cube(void);

	Face* getFaceFront(void);
	Face* getFaceSide(void);
	Face* getFaceUp(void);

	void setFaces(Face* f1, Face* f2, Face* f3);
	vector<Face*> getFaces(void);

private:
	vector<Face*> mFaces;

	//   Top
	//  /¯¯/|
	//  |¯¯|/ Side
	//  Front

	int mIndexFront;
	int mIndexSide;
	int mIndexUp;
};

}}}};