#pragma once
#include "ivisitor.h"
#include "igraphic.h"

namespace baluchon { namespace core { namespace services { namespace positioning {

class Transform :
    public IGraphic
{
public:
    Transform(void);

    ~Transform(void);

    virtual void add(IGraphic* child);
    virtual void remove(int pos);
    virtual vector<IGraphic*> getChildren();
    virtual void apply(CvMat* mul);
    virtual CvMat* getMatrix();
    virtual void setMatrix(CvMat* matrix);
    virtual void accept(IVisitor* v);
    virtual void reset();

protected:
    vector<IGraphic*> mChildren;
    CvMat* mMat;
    CvMat* mTransformedMat;
};

}}}};
