#pragma once

#include <cv.h>

#include "CppInterface.h"

namespace Baluchon { namespace Core { namespace Services {

DeclareInterface(IService)
   virtual void execute(IplImage* img) = 0;
EndInterface

}}};