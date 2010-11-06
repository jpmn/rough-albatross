#pragma once

#include "IService.h"

namespace Baluchon { namespace Core { namespace Services {

class CContoursService : implements IService
{
public:
	CContoursService(void);
	~CContoursService(void);

	void execute(const IplImage* imgIn, IplImage* imgOut);
	void initialize(void);
	void initializeDone(void);
	void reset(void);
};

}}};