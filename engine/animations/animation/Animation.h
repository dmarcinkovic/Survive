//
// Created by david on 01. 10. 2020..
//

#ifndef SURVIVE_ANIMATION_H
#define SURVIVE_ANIMATION_H


#include <vector>
#include "KeyFrame.h"

class Animation
{
private:
	float m_Length;
	std::vector<KeyFrame> m_KeyFrames;

public:
	Animation(float lengthInSeconds, std::vector<KeyFrame> keyFrames);

	[[nodiscard]] float getLength() const;

	[[nodiscard]] const std::vector<KeyFrame> &keyFrames() const;
};


#endif //SURVIVE_ANIMATION_H
