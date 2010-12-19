#pragma once

#include <cv.h>

#include "AnimatedTransform.h"

using namespace baluchon::core::services::positioning;

namespace baluchon { namespace core { namespace datas { namespace animation {

class AnimatedRotation : public AnimatedTransform
{
public:
	AnimatedRotation(CvPoint3D32f axis, float angle, float increment);
	virtual ~AnimatedRotation(void);

	virtual void applyIncrement(void);

private:
	CvPoint3D32f mAxis;
	float mAngle;
	float mIncrement;
};

}}}};