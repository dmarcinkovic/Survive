//
// Created by david on 06. 03. 2021..
//

#ifndef SURVIVE_ANIMATIONCOMPONENT_H
#define SURVIVE_ANIMATIONCOMPONENT_H

#include "Joint.h"

namespace Survive
{
	struct AnimationComponent
	{
		Joint rootJoint;
		int numberOfJoints{};

		std::vector<glm::mat4> jointTransforms;

		AnimationComponent() = default;

		AnimationComponent(Joint rootJoint, int numberOfJoints)
				: rootJoint(std::move(rootJoint)), numberOfJoints(numberOfJoints)
		{}
	};
}

#endif //SURVIVE_ANIMATIONCOMPONENT_H
