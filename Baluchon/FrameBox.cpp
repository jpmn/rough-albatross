#include "FrameBox.h"

#include "RectangularFacet.h"
#include "MathUtility.h"

using namespace baluchon::utilities;

namespace baluchon { namespace core { namespace services { namespace positioning { 

FrameBox::FrameBox(BoxPrism* box, CvScalar color) {

	mColor = color;

	RectangularFacet* fFront = box->getFrontFacet();
	RectangularFacet* fSide = box->getSideFacet();
	RectangularFacet* fTop = box->getTopFacet();

	CvPoint ptTopLeft;
	CvPoint ptTop;
	CvPoint ptTopRight;
	CvPoint ptBottomRight;
	CvPoint ptBottom;
	CvPoint ptBottomLeft;
	CvPoint ptCenter;

	// Contours
	if (fTop->getTopRightVertex().x > fTop->getBottomRightVertex().x) {

		ptTopLeft = MathUtility::intersect(fFront->getBottomLeftVertex(), fFront->getTopLeftVertex(), fTop->getBottomLeftVertex(), fTop->getTopLeftVertex());
		//ptTopLeft = MathUtility::middle(fFront->getTopLeftVertex(), fTop->getBottomLeftVertex()); 

		ptTop = fTop->getTopLeftVertex();

		ptTopRight = MathUtility::intersect(fSide->getBottomRightVertex(), fSide->getTopRightVertex(), fTop->getTopRightVertex(), fTop->getTopLeftVertex());
		//ptTopRight = MathUtility::middle(fSide->getTopRightVertex(), fTop->getTopRightVertex());

		ptBottomRight = fSide->getBottomRightVertex();

		ptBottom = MathUtility::intersect(fFront->getBottomLeftVertex(), fFront->getBottomRightVertex(), fSide->getBottomLeftVertex(), fSide->getBottomRightVertex());
		//ptBottom = MathUtility::middle(fFront->getBottomRightVertex(), fSide->getBottomLeftVertex());
		
		ptBottomLeft = fFront->getBottomLeftVertex();

		ptCenter = MathUtility::middle(fFront->getTopRightVertex(), fTop->getBottomRightVertex());
		ptCenter = MathUtility::middle(ptCenter, fSide->getTopLeftVertex());
	}
	else {
		
		ptTopLeft = MathUtility::intersect(fFront->getBottomLeftVertex(), fFront->getTopLeftVertex(), fTop->getTopLeftVertex(), fTop->getTopRightVertex());
		//ptTopLeft = MathUtility::middle(fFront->getTopLeftVertex(), fTop->getTopLeftVertex()); 
		
		ptTop = fTop->getTopRightVertex();

		ptTopRight = MathUtility::intersect(fSide->getBottomRightVertex(), fSide->getTopRightVertex(), fTop->getBottomRightVertex(), fTop->getTopRightVertex());
		//ptTopRight = MathUtility::middle(fSide->getTopRightVertex(), fTop->getBottomRightVertex());

		ptBottomRight = fSide->getBottomRightVertex();

		ptBottom = MathUtility::intersect(fFront->getBottomLeftVertex(), fFront->getBottomRightVertex(), fSide->getBottomLeftVertex(), fSide->getBottomRightVertex());
		//ptBottom = MathUtility::middle(fFront->getBottomRightVertex(), fSide->getBottomLeftVertex());

		ptBottomLeft = fFront->getBottomLeftVertex();

		ptCenter = MathUtility::middle(fFront->getTopRightVertex(), fTop->getBottomLeftVertex());
		ptCenter = MathUtility::middle(ptCenter, fSide->getTopLeftVertex());
	}

	mListPoints.push_back(ptTopLeft);
	mListPoints.push_back(ptTop);
	mListPoints.push_back(ptTopRight);
	mListPoints.push_back(ptBottomRight);
	mListPoints.push_back(ptBottom);
	mListPoints.push_back(ptBottomLeft);
	mListPoints.push_back(ptCenter);
}


FrameBox::~FrameBox(void) {

}

void FrameBox::accept(IVisitor* v) {   
    v->visit(this);
}

vector<CvPoint> FrameBox::getListPoints() {
	return mListPoints;
}

}}}};
