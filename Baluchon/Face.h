#pragma once

#include <cv.h>
#include <vector>

using namespace std;

namespace baluchon { namespace core { namespace services { namespace objectdetection {

class Face
{
public:
	Face(void);
	~Face(void);

	CvPoint getVertexTopLeft(void);
	CvPoint getVertexTopRight(void);
	CvPoint getVertexBottomLeft(void);
	CvPoint getVertexBottomRight(void);

	void setVertices(CvPoint pt1, CvPoint pt2, CvPoint pt3, CvPoint pt4);
	vector<CvPoint> getVertices(void);

	CvPoint getCenterPosition(void);

private:
	vector<CvPoint> mVertices;

	int mIndexTopLeft;
	int mIndexTopRight;
	int mIndexBottomLeft;
	int mIndexBottomRight;
};

}}}};