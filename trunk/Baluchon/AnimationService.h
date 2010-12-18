#pragma once

#include "IAnimationService.h"

namespace baluchon { namespace core { namespace services { namespace animation {

class AnimationService : public IAnimationService
{
public:
	AnimationService(void);
	virtual ~AnimationService(void);

	virtual void init(void);
	virtual void initDone(void);
	virtual void execute(void);
	virtual void reset(void);
	virtual void dispose(void);
};

}}}};