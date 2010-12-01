#pragma once

#include "IObjectDetectionService.h"
#include "ICaptureService.h"
#include "Face.h"
#include "Cube.h"

using namespace baluchon::core::services::capture;

namespace baluchon { namespace core { namespace services { namespace objectdetection {

class ObjectDetectionService : public IObjectDetectionService
{
public:
	ObjectDetectionService(void);
	~ObjectDetectionService(void);

	virtual void init(void);
	virtual void initDone(void);
	virtual void execute(void);
	virtual void reset(void);
	virtual void dispose(void);

	virtual void setCornerTolerance(int tolerance);

	virtual void drawFace(IplImage* img, Face* f, CvFont font, CvScalar color, bool showNumbers);
	virtual void drawCube(IplImage* img, Cube* c, CvScalar color);

private:
	ICaptureService* mCaptureService;
	int mCornerTolerance;
};

}}}};