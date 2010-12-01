#include "MathUtility.h"

namespace baluchon { namespace utilities {

double MathUtility::findAngle(CvPoint* pt0, CvPoint* pt1, CvPoint* pt2) {
 
	double dx1 = pt1->x - pt0->x; 
	double dy1 = pt1->y - pt0->y; 
	double dx2 = pt2->x - pt0->x; 
	double dy2 = pt2->y - pt0->y; 

	return ( dx1*dx2 + dy1*dy2 ) / sqrt( (dx1*dx1 + dy1*dy1) * (dx2*dx2 + dy2*dy2) + 1e-10 ); 
}

CvPoint MathUtility::findIntersectionPoint(CvPoint pt0, CvPoint pt1, double intersect) {

	int dx = pt0.x + pt1.x;
	int dy = pt0.y + pt1.y;

	return cvPoint(dx*intersect, dy*intersect);
}

double MathUtility::findDistance(CvPoint pt0, CvPoint pt1, CvPoint pt2) {

	return std::sqrt(std::pow((double)pt0.x-pt1.x-pt2.x, 2) + std::pow((double)pt0.y-pt1.y-pt2.y, 2));
}

double MathUtility::findDistance(CvPoint pt0, CvPoint pt1) {

	return std::sqrt(std::pow((double)pt0.x-pt1.x, 2) + std::pow((double)pt0.y-pt1.y, 2));
}

bool MathUtility::sortByDistanceFromOrigin(const CvPoint& pt0, const CvPoint& pt1)
{
	int dpt0 = std::sqrt(std::pow((double)pt0.x-0,2) + std::pow((double)pt0.y-0,2));
	int dpt1 = std::sqrt(std::pow((double)pt1.x-0,2) + std::pow((double)pt1.y-0,2));

  return dpt0 < dpt1;
}

bool MathUtility::sortByX(const CvPoint& pt0, const CvPoint& pt1) {
	return pt0.x < pt1.x;
}

bool MathUtility::sortByCenterPositionX(Face* f0, Face* f1) {
	return f0->getCenterPosition().x < f1->getCenterPosition().x;
}

bool MathUtility::sortByY(const CvPoint& pt0, const CvPoint& pt1) {
	return pt0.y < pt1.y;
}

bool MathUtility::sortByCenterPositionY(Face* f0, Face* f1) {
	return f0->getCenterPosition().y < f1->getCenterPosition().y;
}

}};