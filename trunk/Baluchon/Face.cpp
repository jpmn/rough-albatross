#include "Face.h"

#include "MathUtility.h"

using namespace baluchon::utilities;

namespace baluchon { namespace core { namespace services { namespace objectdetection {

Face::Face(void) {
	
}


Face::~Face(void) {

}

CvPoint Face::getVertexTopLeft(void) {
	return mVertices[mIndexTopLeft];
}

CvPoint Face::getVertexTopRight(void) {
	return mVertices[mIndexTopRight];
}

CvPoint Face::getVertexBottomLeft(void) {
	return mVertices[mIndexBottomLeft];
}

CvPoint Face::getVertexBottomRight(void) {
	return mVertices[mIndexBottomRight];
}

void Face::setVertices(CvPoint pt1, CvPoint pt2, CvPoint pt3, CvPoint pt4) {

	mVertices.push_back(pt1);
	mVertices.push_back(pt2);
	mVertices.push_back(pt3);
	mVertices.push_back(pt4);

	std::sort(mVertices.begin(), mVertices.end(), MathUtility::sortByX);

	if (mVertices[1].y > mVertices[0].y) {
		mIndexTopLeft = 0;
		mIndexBottomLeft = 1;

		if (mVertices[2].y < mVertices[3].y) {
			mIndexTopRight = 2;
			mIndexBottomRight = 3;
		}
		else {
			mIndexTopRight = 3;
			mIndexBottomRight = 2;
		}
	}
	else {
		mIndexTopLeft = 1;
		mIndexBottomLeft = 0;

		if (mVertices[2].y < mVertices[3].y) {
			mIndexTopRight = 2;
			mIndexBottomRight = 3;
		}
		else {
			mIndexTopRight = 3;
			mIndexBottomRight = 2;
		}
	}
}

vector<CvPoint> Face::getVertices(void) {
	return mVertices;
}

CvPoint Face::getCenterPosition(void) {
	return MathUtility::findIntersectionPoint(getVertexTopLeft(), getVertexBottomRight(), 0.5);
}

}}}};