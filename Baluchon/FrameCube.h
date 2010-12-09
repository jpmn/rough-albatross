#pragma once
#include "igraphic.h"
#include "ivisitor.h"

namespace baluchon { namespace core { namespace services { namespace positioning { 

class FrameCube :
    public IGraphic
{
public:
    FrameCube(CvPoint3D32f pt1, float size);
    ~FrameCube(void);

    void accept(IVisitor* v);
};

}}}};
