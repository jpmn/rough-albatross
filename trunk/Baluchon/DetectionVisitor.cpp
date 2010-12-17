#include "DetectionVisitor.h"
#include "FrameCube.h"
#include "Transform.h"
#include "FrameBox.h"

namespace baluchon { namespace core { namespace services { namespace positioning { 

DetectionVisitor::DetectionVisitor(void) {

}

DetectionVisitor::~DetectionVisitor(void) {

}

void DetectionVisitor::visit(FrameCube* fc) {

}

void DetectionVisitor::visit(Transform* tfrm) {

}

void DetectionVisitor::visit(FrameBox* fb) {

	vector<CvPoint> wListPoints = fb->getListPoints();

	// contour de la boite
	for (unsigned int i = 0; i < 5; i++) {
		cvLine(mSrcImg, wListPoints[i], wListPoints[i+1], fb->getColor(), 3, 8);
	}
	
	// fermer la boucle
	cvLine(mSrcImg, wListPoints[5], wListPoints[0], fb->getColor(), 3, 8);

	// arrêtes vers le point commun aux trois faces
	cvLine(mSrcImg, wListPoints[0], wListPoints[6], fb->getColor(), 3, 8);
	cvLine(mSrcImg, wListPoints[2], wListPoints[6], fb->getColor(), 3, 8);
	cvLine(mSrcImg, wListPoints[4], wListPoints[6], fb->getColor(), 3, 8);
}

void DetectionVisitor::setImage(IplImage *img) {
    mSrcImg = img;
}

}}}};