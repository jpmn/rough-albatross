#include "RectangleDetector.h"

#include "MathUtility.h"

using namespace baluchon::utilities;

namespace baluchon { namespace core { namespace services { namespace objectdetection {

RectangleDetector::RectangleDetector(void) {
	mFacetFactory = new FacetFactory();
}

RectangleDetector::~RectangleDetector(void) {
	delete mFacetFactory;
}

vector<IDetectable*> RectangleDetector::find(IplImage* img, IplImage* src) {
	vector<RectangularFacet*> wListFacets;

	CvSeq* contours = 0; 
	CvMemStorage* storage = cvCreateMemStorage(0); 

	//CV_RETR_CCOMP, CV_RETR_LIST, CV_RETR_EXTERNAL
	cvFindContours(img, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

	while (contours != NULL) {
		CvSeq* approx = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02);

		// Un carré est un polygon convexe
		// Un carré a seulement 4 segments
		// Un carré de taille intéressante
		if (cvCheckContourConvexity(approx) && approx->total == 4 && cvContourArea(approx, CV_WHOLE_SEQ) > 1000) {

			double s = 0.0f; 
			double t = 0.0f;
			for(int i = 0; i < 5; i++ ) 
			{ 
				// find minimum angle between joint 
				// edges (maximum of cosine) 
				if( i >= 2 ) 
				{ 
					t = std::fabs(MathUtility::angle((CvPoint*)cvGetSeqElem(approx, i), (CvPoint*)cvGetSeqElem(approx, i-2), (CvPoint*)cvGetSeqElem(approx, i-1))); 
					s = s > t ? s : t; 
				}
			}

			if (s > 0.3) { 
				CvPoint pt1 = *(CvPoint*)cvGetSeqElem(approx, 0);
				CvPoint pt2 = *(CvPoint*)cvGetSeqElem(approx, 1);
				CvPoint pt3 = *(CvPoint*)cvGetSeqElem(approx, 2);
				CvPoint pt4 = *(CvPoint*)cvGetSeqElem(approx, 3);

				RectangularFacet* facet = mFacetFactory->createRectangularFacet(pt1, pt2, pt3, pt4);
				
				wListFacets.push_back(facet);

				/*
				cvLine(src, facet->getTopLeftVertex(), facet->getTopRightVertex(), CV_RGB(255,0,0), 3);
				cvLine(src, facet->getTopRightVertex(), facet->getBottomRightVertex(), CV_RGB(0,255,0), 3);
				cvLine(src, facet->getBottomRightVertex(), facet->getBottomLeftVertex(), CV_RGB(0,0,255), 3);
				cvLine(src, facet->getBottomLeftVertex(), facet->getTopLeftVertex(), CV_RGB(255,0,255), 3);
				*/
			}
		}

		contours = contours->h_next;
	}

	cvReleaseMemStorage(&storage);

	vector<IDetectable*> wListDetectables(wListFacets.begin(), wListFacets.end());

	return wListDetectables;
}

}}}};