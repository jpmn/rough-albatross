#include "ObjectDetectionService.h"

#include <cv.h>
#include <cmath>

#include "IServiceLayer.h"
#include "CameraCaptureService.h"
#include "MathUtility.h"
#include "Cube.h"

using namespace baluchon::utilities;

namespace baluchon { namespace core { namespace services { namespace objectdetection {

ObjectDetectionService::ObjectDetectionService(void) {

}

ObjectDetectionService::~ObjectDetectionService(void) {

}

void ObjectDetectionService::init(void) {
	mCaptureService = new CameraCaptureService();
	mCaptureService = (ICaptureService*) mServiceLayer->findService(mCaptureService);
}

void ObjectDetectionService::initDone(void) {
	cvNamedWindow("Gray", 1);
	cvNamedWindow("Canny", 1);
	cvNamedWindow("Contours", 1);
}

void ObjectDetectionService::execute(void) {
	IplImage* imgIn = mCaptureService->getImage();
	
	IplImage* mImageGray = cvCreateImage(cvGetSize(imgIn), IPL_DEPTH_8U, 1);
	IplImage* mImageEdges = cvCreateImage(cvGetSize(imgIn), IPL_DEPTH_32F, 1);
	IplImage* mImageContours = cvCreateImage(cvGetSize(imgIn), IPL_DEPTH_8U, 1);
	IplImage* mImageColors = cvCreateImage(cvGetSize(imgIn), IPL_DEPTH_8U, 3);

	cvCvtColor(imgIn, mImageGray, CV_BGR2GRAY);

	//cvAdaptiveThreshold(mImageGray, mImageGray, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 3); 
	//cvLaplace(mImageGray, mImageEdges, 7);
	//cvConvertScale(mImageEdges, mImageContours);
	//cvCanny(mImageGray, mImageContours, 0, 100, 3);

	cvSmooth(mImageGray, mImageGray, CV_MEDIAN, 7, 0);
	cvShowImage("Canny", mImageGray);
	cvCanny(mImageGray, mImageContours, 0, 200, 3);
	cvDilate(mImageContours, mImageContours, NULL, 3);

	cvShowImage("Gray", mImageContours);
	
	CvSeq* contours = 0; 
	CvMemStorage* storage = cvCreateMemStorage(0); 

	//CV_RETR_CCOMP, CV_RETR_LIST, CV_RETR_EXTERNAL
	cvFindContours(mImageContours, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

	//cvZero(mImageContours);
	vector<CvPoint> list;
	vector<Face*> wListFaces;
	Cube* wCube = new Cube();

	while (contours != NULL) {
		CvSeq* approx = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02);

		//if (cvContourArea(approx, CV_WHOLE_SEQ) > 1000)
			//cvDrawContours(mImageColors, approx, CV_RGB(rand()%255, rand()%255, rand()%255), CV_RGB(rand()%255, rand()%255, rand()%255),0,3,8);

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
					t = fabs(MathUtility::findAngle( 
						(CvPoint*)cvGetSeqElem(approx, i), 
						(CvPoint*)cvGetSeqElem(approx, i-2), 
						(CvPoint*)cvGetSeqElem(approx, i-1)
					)); 
					s = s > t ? s : t; 
				}
			}

			if (s > 0.3) { 
				CvPoint* pt1 = (CvPoint*)cvGetSeqElem(approx, 0);
				CvPoint* pt2 = (CvPoint*)cvGetSeqElem(approx, 1);
				CvPoint* pt3 = (CvPoint*)cvGetSeqElem(approx, 2);
				CvPoint* pt4 = (CvPoint*)cvGetSeqElem(approx, 3);

				Face* f = new Face();
				f->setVertices(*pt1, *pt2, *pt3, *pt4);

				wListFaces.push_back(f);

				// Tous les polygones à 4 cotés trouvés...
				//CvScalar color = CV_RGB(255, 255, 0);
				//cvDrawContours(imgIn, approx, color, color, 0, 3, 8);
			}
		}

		contours = contours->h_next;
	}

	if (wListFaces.size() >= 3) {
		// Trouver 3 faces avec un sommet commun
		bool found = false;
		for (int i = 0; i < wListFaces.size() && !found; i++) {
			Face* f1 = wListFaces[i];

			for (int j = 0; j < wListFaces.size() && !found; j++) {
				Face* f2 = wListFaces[j];

				for (int k = 0; k < wListFaces.size() && !found; k++) {
					Face* f3 = wListFaces[k];

					if (f1 != f2 && f2 != f3 && f3 != f1) {
						CvPoint dpt = MathUtility::findIntersectionPoint(f1->getVertexTopRight(), f2->getVertexTopLeft(), 0.5);

						if (f3->getVertexTopRight().x < f3->getVertexBottomRight().x)
							dpt = MathUtility::findIntersectionPoint(dpt, f3->getVertexBottomLeft(), 0.5);
						else 
							dpt = MathUtility::findIntersectionPoint(dpt, f3->getVertexBottomRight(), 0.5);

						double dt1 = MathUtility::findDistance(f1->getVertexTopRight(), dpt);
						double dt2 = MathUtility::findDistance(f2->getVertexTopLeft(), dpt);
						double dt3;
						
						if (f3->getVertexTopRight().x < f3->getVertexBottomRight().x)
							dt3 = MathUtility::findDistance(f3->getVertexBottomLeft(), dpt);
						else 
							dt3 = MathUtility::findDistance(f3->getVertexBottomRight(), dpt);

						if (dt1 < mCornerTolerance && dt2 < mCornerTolerance && dt3 < mCornerTolerance) {
							cvDrawCircle(imgIn, dpt, 10, CV_RGB(255, 0, 255), -1, 8);
							wCube->setFaces(wListFaces[i], wListFaces[j], wListFaces[k]);
							found = true;
						}
					}
				}
			}
		}

		if (found) {
			CvFont font;
			cvInitFont(&font, CV_FONT_HERSHEY_PLAIN, 1.0, 1.0, 0, 1, CV_AA);

			//drawFace(imgIn, wCube->getFaceFront(), font, CV_RGB(255, 0, 0), true); 
			//drawFace(imgIn, wCube->getFaceSide(), font, CV_RGB(0, 0, 255), true); 
			//drawFace(imgIn, wCube->getFaceUp(), font, CV_RGB(0, 255, 0), true); 

			drawCube(imgIn, wCube, CV_RGB(0, 255, 255));
		}
	}

	cvShowImage("Contours", mImageColors);
	
	cvReleaseMemStorage(&storage);
	cvReleaseImage(&mImageColors);
	cvReleaseImage(&mImageEdges);
	cvReleaseImage(&mImageContours);
	cvReleaseImage(&mImageGray);
}

void ObjectDetectionService::reset(void) {

}

void ObjectDetectionService::dispose(void) {
	cvDestroyWindow("Gray");
	cvDestroyWindow("Canny");
	cvDestroyWindow("Contours");
}

void ObjectDetectionService::setCornerTolerance(int tolerance) {
	mCornerTolerance = tolerance;
}

void ObjectDetectionService::drawFace(IplImage* img, Face* f, CvFont font, CvScalar color, bool showNumbers) {

	cvDrawLine(img, f->getVertexTopLeft(), f->getVertexBottomLeft(), color, 3, 8);
	cvDrawLine(img, f->getVertexBottomLeft(), f->getVertexBottomRight(), color, 3, 8);
	cvDrawLine(img, f->getVertexBottomRight(), f->getVertexTopRight(), color, 3, 8);
	cvDrawLine(img, f->getVertexTopRight(), f->getVertexTopLeft(), color, 3, 8);

	if (showNumbers) {
		cvPutText(img, "1", f->getVertexTopLeft(), &font, color);
		cvPutText(img, "2", f->getVertexBottomLeft(), &font, color);
		cvPutText(img, "3", f->getVertexBottomRight(), &font, color);
		cvPutText(img, "4", f->getVertexTopRight(), &font, color);
	}
}

void ObjectDetectionService::drawCube(IplImage* img, Cube* c, CvScalar color) {
	
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_PLAIN, 1.0, 1.0, 0, 1, CV_AA);

	Face* fFront = c->getFaceFront();
	Face* fSide = c->getFaceSide();
	Face* fUp = c->getFaceUp();

	CvPoint ptLeft;
	CvPoint ptRight;
	CvPoint ptBottom;

	CvPoint ptCenter;

	// Contours
	if (fUp->getVertexTopRight().x > fUp->getVertexBottomRight().x) {
		ptLeft = MathUtility::findIntersectionPoint(fFront->getVertexTopLeft(), fUp->getVertexBottomLeft(), 0.5); 
		ptRight = MathUtility::findIntersectionPoint(fSide->getVertexTopRight(), fUp->getVertexTopRight(), 0.5);
		ptBottom = MathUtility::findIntersectionPoint(fFront->getVertexBottomRight(), fSide->getVertexBottomLeft(), 0.5);

		ptCenter = MathUtility::findIntersectionPoint(fFront->getVertexTopRight(), fUp->getVertexBottomRight(), 0.5);
		ptCenter = MathUtility::findIntersectionPoint(ptCenter, fSide->getVertexTopLeft(), 0.5);

		cvDrawLine(img, ptLeft, fUp->getVertexTopLeft(), color, 3, 8);
		cvDrawLine(img, fUp->getVertexTopLeft(), ptRight, color, 3, 8);

		cvDrawLine(img, ptRight, fSide->getVertexBottomRight(), color, 3, 8);
		cvDrawLine(img, fSide->getVertexBottomRight(), ptBottom, color, 3, 8);
		cvDrawLine(img, ptBottom, fFront->getVertexBottomLeft(), color, 3, 8);
		cvDrawLine(img, fFront->getVertexBottomLeft(), ptLeft, color, 3, 8);
	}
	else {
		ptLeft = MathUtility::findIntersectionPoint(fFront->getVertexTopLeft(), fUp->getVertexTopLeft(), 0.5); 
		ptRight = MathUtility::findIntersectionPoint(fSide->getVertexTopRight(), fUp->getVertexBottomRight(), 0.5);
		ptBottom = MathUtility::findIntersectionPoint(fFront->getVertexBottomRight(), fSide->getVertexBottomLeft(), 0.5);

		ptCenter = MathUtility::findIntersectionPoint(fFront->getVertexTopRight(), fUp->getVertexBottomLeft(), 0.5);
		ptCenter = MathUtility::findIntersectionPoint(ptCenter, fSide->getVertexTopLeft(), 0.5);

		cvDrawLine(img, ptLeft, fUp->getVertexTopRight(), color, 3, 8);
		cvDrawLine(img, fUp->getVertexTopRight(), ptRight, color, 3, 8);

		cvDrawLine(img, ptRight, fSide->getVertexBottomRight(), color, 3, 8);
		cvDrawLine(img, fSide->getVertexBottomRight(), ptBottom, color, 3, 8);
		cvDrawLine(img, ptBottom, fFront->getVertexBottomLeft(), color, 3, 8);
		cvDrawLine(img, fFront->getVertexBottomLeft(), ptLeft, color, 3, 8);
	}

	// Center
	cvDrawLine(img, ptLeft, ptCenter, color, 3, 8);
	cvDrawLine(img, ptBottom, ptCenter, color, 3, 8);
	cvDrawLine(img, ptRight, ptCenter, color, 3, 8);
}

}}}};