#include "AnimationSequence.h"

namespace baluchon { namespace core { namespace datas { namespace animation {

AnimationSequence::AnimationSequence(void) {

}

AnimationSequence::~AnimationSequence(void) {

}

void AnimationSequence::addAnimation(IAnimation* animation) {
	mListAnimations.push_back(animation);
}

void AnimationSequence::execute() {
	if (mListAnimations.size() == 0)
		return;

	IAnimation* anim = mListAnimations[0];
	
	anim->forward();

	if (anim->isDone())
		mListAnimations.erase(mListAnimations.begin());
}

}}}};