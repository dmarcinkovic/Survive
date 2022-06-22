//
// Created by david on 06. 03. 2021..
//

#ifndef SURVIVE_ANIMATIONCOMPONENT_H
#define SURVIVE_ANIMATIONCOMPONENT_H

#include "Joint.h"
#include "Animator.h"

namespace Survive
{
	struct AnimationComponent
	{
		Joint rootJoint;
		int numberOfJoints{};
		Animator animator;

		std::vector<glm::mat4> jointTransforms;

		AnimationComponent()
				: animator(Animation(0, {}))
		{}

		AnimationComponent(Animator animator, Joint rootJoint, int numberOfJoints)
				: animator(std::move(animator)), rootJoint(std::move(rootJoint)), numberOfJoints(numberOfJoints)
		{}
	};
}

#endif //SURVIVE_ANIMATIONCOMPONENT_H
