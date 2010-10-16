#pragma once

#include "CppInterface.h"

namespace Baluchon { namespace Core { namespace Services {

DeclareInterface(IService)
   virtual void execute(void) = 0;
EndInterface

}}};