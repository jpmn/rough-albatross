#pragma once

#include "IAnimation.h"

namespace baluchon { namespace core { namespace datas { namespace animation {

class Animation : public IAnimation
{
public:
	Animation(void);
	virtual ~Animation(void);

	void setTranslation(Translation* translation, float speed);
	void setRotation(Rotation* rotation, float speed);
	void setScale(Scaling* scaling, float speed);

	void forward(void);
	void backward(void);
	bool isDone(void);
};

}}}};