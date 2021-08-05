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

	private:
		void calculateJointTransforms()
		{
			jointTransforms = std::vector<glm::mat4>(numberOfJoints);
			addJointsToArray(rootJoint, jointTransforms);
		}

		void addJointsToArray(const Joint &headJoint, std::vector<glm::mat4> &jointMatrices)
		{
			jointMatrices[headJoint.index()] = headJoint.getAnimatedTransform();
			for (auto const &childJoint : headJoint.children())
			{
				addJointsToArray(childJoint, jointMatrices);
			}
		}
	};
}

#endif //SURVIVE_ANIMATIONCOMPONENT_H
