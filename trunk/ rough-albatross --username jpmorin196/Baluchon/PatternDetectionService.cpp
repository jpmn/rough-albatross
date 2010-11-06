#include <iostream>

#include "PatternDetectionService.h"

namespace Baluchon { namespace Core { namespace Services {

CPatternDetectionService::CPatternDetectionService(void)
{
}


CPatternDetectionService::~CPatternDetectionService(void)
{
}

void CPatternDetectionService::execute(const IplImage* imgIn, IplImage* imgOut) {
	printf("PatternDetectionService\n");
}

void CPatternDetectionService::initialize(void) {

}

void CPatternDetectionService::initializeDone(void) {

}

void CPatternDetectionService::reset(void) {

}

}}};