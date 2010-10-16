#pragma once

#include "IService.h"

namespace Baluchon { namespace Core { namespace Services {

class CColorDetectionService : implements IService
{
public:
	CColorDetectionService(void);
	~CColorDetectionService(void);

	void execute(void);
};

}}};