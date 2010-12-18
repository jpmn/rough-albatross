#pragma once

#include "AnimationSequence.h"

namespace baluchon { namespace core { namespace datas { namespace animation {

class IAnimable {
public:
	virtual ~IAnimable(void) {}

	void setAnimationSequence(AnimationSequence* sequence) {
		mAnimationSequence = sequence;
	}

	AnimationSequence* getAnimationSequence(void) {
		return mAnimationSequence;
	}

private:
	AnimationSequence* mAnimationSequence;
};

}}}};