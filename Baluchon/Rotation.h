#pragma once
#include "transform.h"

namespace baluchon { namespace core { namespace services { namespace positioning { 

class Rotation :
    public Transform
{
public:
    Rotation(float angle, float x, float y, float z);
    ~Rotation(void);
};

}}}};
