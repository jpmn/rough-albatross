#pragma once
#include "IVisitor.h"
#include "cv.h"

namespace baluchon { namespace core { namespace services { namespace positioning { 

class FrameCube;
class Transform;
class FrameBox;

class DetectionVisitor : public IVisitor
{
public:
	DetectionVisitor(void);
	virtual ~DetectionVisitor(void);

	void visit(FrameCube *fc);
    void visit(Transform *t);
	void visit(FrameBox *fb);

    void setImage(IplImage* img);

private:
    IplImage* mSrcImg;
};

}}}};