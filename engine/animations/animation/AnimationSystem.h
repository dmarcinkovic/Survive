//
// Created by david on 05. 08. 2021..
//

#ifndef SURVIVE_ANIMATIONSYSTEM_H
#define SURVIVE_ANIMATIONSYSTEM_H

#include <vector>

#include "entt.hpp"
#include "AnimationComponent.h"
#include "Joint.h"

namespace Survive
{
	class AnimationSystem
	{
	public:
		static void update(entt::registry &registry);

	private:
		static void calculateJointTransforms(AnimationComponent &animationComponent);

		static void addJointsToArray(const Joint &headJoint, std::vector<glm::mat4> &jointMatrices);
	};
}

#endif //SURVIVE_ANIMATIONSYSTEM_H
