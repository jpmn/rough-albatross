#pragma once

#include "Translation.h"
#include "Rotation.h"
#include "Scaling.h"

using namespace baluchon::core::services::positioning;

namespace baluchon { namespace core { namespace datas { namespace animation {

class IAnimation {
public:
	virtual ~IAnimation(void) {}

	virtual void setTranslation(Translation* translation, float speed) = 0;
	virtual void setRotation(Rotation* rotation, float speed) = 0;
	virtual void setScale(Scaling* scaling, float speed) = 0;

	virtual void forward(void) = 0;
	virtual void backward(void) = 0;
	virtual bool isDone(void) = 0;
};

}}}};