#include <highgui.h>

#include "ContoursService.h"

namespace Baluchon { namespace Core { namespace Services {

CContoursService::CContoursService(void)
{
	cvNamedWindow("Contours", 1);
}


CContoursService::~CContoursService(void)
{
	cvDestroyWindow("Contours");
}

void CContoursService::execute(const IplImage* imgIn, IplImage* imgOut) {
	IplImage* img_8uc1 = cvCreateImage( cvGetSize(imgIn), 8, 1);
	IplImage* img_edge = cvCreateImage( cvGetSize(img_8uc1), 8, 1 );
	IplImage* img_8uc3 = cvCreateImage( cvGetSize(img_8uc1), 8, 3 );

	cvCvtColor(imgIn, img_8uc1, CV_BGR2GRAY);
	cvThreshold( img_8uc1, img_edge, 128, 255, CV_THRESH_BINARY );

	CvMemStorage* storage = cvCreateMemStorage();
	CvSeq* first_contour = NULL;

	int Nc = cvFindContours(
		img_edge,
		storage,
		&first_contour,
		sizeof(CvContour),
		CV_RETR_LIST );

	int n=0;
	printf( "Total Contours Detected: %d\n", Nc );
	CvScalar red = CV_RGB(250,0,0);
	CvScalar blue = CV_RGB(0,0,250);
	
	for( CvSeq* c=first_contour; c!=NULL; c=c->h_next ){
		cvCvtColor( img_8uc1, img_8uc3, CV_GRAY2BGR );
		cvDrawContours(
			img_8uc3,
			c,
			red,		// Red
			blue,		// Blue
			1,			// Vary max_level and compare results
			2,
			8 );

		for( int i=0; i < c->total; ++i ){
			CvPoint* p = CV_GET_SEQ_ELEM( CvPoint, c, i );
		}
		n++;
	}

	cvCvtColor( img_8uc1, img_8uc3, CV_GRAY2BGR );
	cvShowImage("Contours", img_8uc1);
	
	cvReleaseImage( &img_8uc1 );
	cvReleaseImage( &img_8uc3 );
	cvReleaseImage( &img_edge );
}

void CContoursService::initialize(void) {

}

void CContoursService::initializeDone(void) {

}

void CContoursService::reset(void) {

}

}}};