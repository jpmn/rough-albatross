#pragma once

#include <cv.h>

#include "AnimatedTransform.h"

using namespace baluchon::core::services::positioning;

namespace baluchon { namespace core { namespace datas { namespace animation {

class AnimatedSliding : public AnimatedTransform
{
public:
	AnimatedSliding(CvPoint3D32f vector, CvPoint3D32f limit, float increment);
	virtual ~AnimatedSliding(void);

	virtual void applyIncrement(void);

private:
	CvPoint3D32f mVector;
	CvPoint3D32f mLimit;
	CvPoint3D32f mInitial;
	CvPoint3D32f mSide;
	float mIncrement;
};

}}}};