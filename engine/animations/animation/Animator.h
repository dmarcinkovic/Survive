//
// Created by david on 01. 10. 2020..
//

#ifndef SURVIVE_ANIMATOR_H
#define SURVIVE_ANIMATOR_H


#include "Animation.h"
#include "../joints/Joint.h"
#include "KeyFrame.h"
#include "../renderer/AnimationRenderer.h"

class Animator
{
private:
	Animation m_Animation;
	float m_AnimationTime{};

	entt::entity m_Model;

public:
	Animator(Animation animation, entt::entity animatedObject);

	void update(entt::registry  &registry);

private:
	[[nodiscard]] std::unordered_map<std::string, glm::mat4> calculatePose() const;

	void applyPoseToJoints(const std::unordered_map<std::string, glm::mat4> &currentPose, Joint &joint,
						   const glm::mat4 &parentTransformation);

	void increaseAnimationTime();

	[[nodiscard]] std::pair<KeyFrame, KeyFrame> nextAndPreviousFrames() const;

	[[nodiscard]] float calculateProgression(const KeyFrame &prev, const KeyFrame &next) const;

	static std::unordered_map<std::string, glm::mat4>
	interpolatePoses(const KeyFrame &prev, const KeyFrame &next, float progression);
};


#endif //SURVIVE_ANIMATOR_H
