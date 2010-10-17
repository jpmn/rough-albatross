#pragma once

#include "CppInterface.h"
#include "IService.h"

namespace Baluchon { namespace Core { namespace Services {

class CPatternDetectionService : implements IService
{
public:
	CPatternDetectionService(void);
	~CPatternDetectionService(void);

	void execute(IplImage* img);
};

}}};