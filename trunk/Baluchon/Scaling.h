#pragma once
#include "transform.h"

namespace baluchon { namespace core { namespace services { namespace positioning { 

class Scaling :
    public Transform
{
public:
    Scaling(float x, float y, float z);
    ~Scaling(void);
};

}}}};
