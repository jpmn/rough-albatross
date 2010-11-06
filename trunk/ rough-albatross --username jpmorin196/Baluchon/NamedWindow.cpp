#include <highgui.h>

#include "NamedWindow.h"

namespace Baluchon { namespace Core { namespace Components { namespace Windows {

CNamedWindow::CNamedWindow(void)
{
}

CNamedWindow::~CNamedWindow(void)
{
	cvDestroyWindow(mName);
}

void CNamedWindow::init(void) {
	cvNamedWindow(mName, mFlag);
}

void CNamedWindow::show(void) {
	cvShowImage(mName, mImage);
}

void CNamedWindow::setName(const char* name) {
	mName = name;
}

void CNamedWindow::setFlag(int flag) {
	mFlag = flag;
}

void CNamedWindow::setImage(const IplImage* image) {
	mImage = image;
}

const char* CNamedWindow::getName(void) {
	return mName;
}

const IplImage* CNamedWindow::getImage(void) {
	return mImage;
}

}}}};