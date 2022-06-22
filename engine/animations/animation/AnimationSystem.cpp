//
// Created by david on 05. 08. 2021..
//

#include "AnimationSystem.h"

void Survive::AnimationSystem::update(entt::registry &registry)
{
	auto view = registry.view<AnimationComponent>();

	for (auto const &entity : view)
	{
		AnimationComponent &animationComponent = view.get<AnimationComponent>(entity);
		calculateJointTransforms(animationComponent);
		animationComponent.animator.update(animationComponent.rootJoint);
	}
}

void Survive::AnimationSystem::calculateJointTransforms(Survive::AnimationComponent &animationComponent)
{
	animationComponent.jointTransforms = std::vector<glm::mat4>(animationComponent.numberOfJoints);
	addJointsToArray(animationComponent.rootJoint, animationComponent.jointTransforms);
}

void Survive::AnimationSystem::addJointsToArray(const Joint &headJoint, std::vector<glm::mat4> &jointMatrices)
{
	jointMatrices[headJoint.index()] = headJoint.getAnimatedTransform();
	for (auto const &childJoint : headJoint.children())
	{
		addJointsToArray(childJoint, jointMatrices);
	}
}