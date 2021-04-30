//
// Created by david on 06. 03. 2021..
//

#ifndef SURVIVE_ANIMATIONCOMPONENT_H
#define SURVIVE_ANIMATIONCOMPONENT_H

#include "../animations/joints/Joint.h"

struct AnimationComponent
{
	Joint rootJoint;
	int numberOfJoints{};

	AnimationComponent() = default;

	AnimationComponent(Joint rootJoint, int numberOfJoints)
			: rootJoint(std::move(rootJoint)), numberOfJoints(numberOfJoints)
	{}
};

#endif //SURVIVE_ANIMATIONCOMPONENT_H
