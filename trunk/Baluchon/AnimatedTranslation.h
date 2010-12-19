#pragma once

#include <cv.h>

#include "AnimatedTransform.h"

using namespace baluchon::core::services::positioning;

namespace baluchon { namespace core { namespace datas { namespace animation {

class AnimatedTranslation : public AnimatedTransform
{
public:
	AnimatedTranslation(CvPoint3D32f vector, float increment);
	virtual ~AnimatedTranslation(void);

	virtual void applyIncrement(void);

private:
	CvPoint3D32f mVector;
	float mIncrement;
};

}}}};