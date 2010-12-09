#pragma once
#include "igraphic.h"
#include "ivisitor.h"

namespace baluchon { namespace core { namespace services { namespace positioning { 

class FrameCube :
    public IGraphic
{
public:
    FrameCube(CvPoint3D32f pt1, float size, CvScalar color);
    ~FrameCube(void);

    void accept(IVisitor* v);
    void setColor(CvScalar color);
    CvScalar getColor();

private:
    CvScalar mColor;
};

}}}};
