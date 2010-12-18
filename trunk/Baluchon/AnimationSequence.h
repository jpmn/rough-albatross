#pragma once

#include <vector>

#include "IAnimation.h"

using namespace std;

namespace baluchon { namespace core { namespace datas { namespace animation {

class AnimationSequence
{
public:
	AnimationSequence(void);
	~AnimationSequence(void);

	void addAnimation(IAnimation* animation);
	void execute();

private:
	vector<IAnimation*> mListAnimations;
};

}}}};