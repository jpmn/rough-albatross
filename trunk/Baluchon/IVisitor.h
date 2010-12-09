#pragma once

namespace baluchon { namespace core { namespace services { namespace positioning { 

class Transform;
class FrameCube;

class IVisitor
{
public:
    ~IVisitor(void) {};

    virtual void visit(Transform *t) = 0;
    virtual void visit(FrameCube *fc) = 0;
};

}}}};
