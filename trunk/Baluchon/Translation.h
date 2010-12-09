#pragma once
#include "transform.h"

namespace baluchon { namespace core { namespace services { namespace positioning { 

class Translation :
    public Transform
{
public:
    Translation(int x, int y, int z);
    ~Translation(void);
};

}}}};
