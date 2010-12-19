#pragma once

#include <cv.h>

#include "AnimatedTransform.h"

using namespace baluchon::core::services::positioning;

namespace baluchon { namespace core { namespace datas { namespace animation {

class AnimatedScaling : public AnimatedTransform
{
public:
	AnimatedScaling(CvPoint3D32f factors, CvPoint3D32f increment);
	virtual ~AnimatedScaling(void);

	virtual void applyIncrement(void);

private:
	CvPoint3D32f mFactors;
	CvPoint3D32f mIncrement;
};

}}}};