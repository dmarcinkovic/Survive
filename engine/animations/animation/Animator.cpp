//
// Created by david on 01. 10. 2020..
//

#include "Animator.h"
#include "../../display/Display.h"
#include "../../components/AnimationComponent.h"

Animator::Animator(Animation animation, entt::entity animatedObject)
		: m_Animation(std::move(animation)), m_Model(animatedObject)
{

}

std::unordered_map<std::string, glm::mat4> Animator::calculatePose() const
{
	auto[prev, next] = nextAndPreviousFrames();
	float progression = calculateProgression(prev, next);

	return interpolatePoses(prev, next, progression);
}

void Animator::applyPoseToJoints(const std::unordered_map<std::string, glm::mat4> &currentPose, Joint &joint,
								 const glm::mat4 &parentTransformation)
{
	glm::mat4 currentLocalTransform = currentPose.at(joint.name());
	glm::mat4 currentTransform = parentTransformation * currentLocalTransform;

	for (auto &child : joint.children())
	{
		applyPoseToJoints(currentPose, child, currentTransform);
	}

	currentTransform *= joint.inverseBindTransform();
	joint.setAnimatedTransform(currentTransform);
}

void Animator::update(entt::registry &registry)
{
	AnimationComponent animationComponent = registry.get<AnimationComponent>(m_Model);

	increaseAnimationTime();
	std::unordered_map<std::string, glm::mat4> currentPose = calculatePose();
	applyPoseToJoints(currentPose, animationComponent.rootJoint, glm::mat4{});
}

void Animator::increaseAnimationTime()
{
	m_AnimationTime += static_cast<float>(Display::getFrameTime());
	if (m_AnimationTime > m_Animation.getLength())
	{
		m_AnimationTime = std::fmod(m_AnimationTime, m_Animation.getLength());
	}
}

std::pair<KeyFrame, KeyFrame> Animator::nextAndPreviousFrames() const
{
	std::vector<KeyFrame> keyFrames = m_Animation.keyFrames();
	KeyFrame previous = keyFrames.front();
	KeyFrame next = keyFrames.front();

	for (int i = 1; i < keyFrames.size(); ++i)
	{
		next = keyFrames[i];
		if (next.timeStamp() > m_AnimationTime)
		{
			break;
		}
		previous = keyFrames[i];
	}

	return {previous, next};
}

float Animator::calculateProgression(const KeyFrame &prev, const KeyFrame &next) const
{
	float totalTime = next.timeStamp() - prev.timeStamp();
	float currentTime = m_AnimationTime - prev.timeStamp();
	return currentTime / totalTime;
}

std::unordered_map<std::string, glm::mat4>
Animator::interpolatePoses(const KeyFrame &prev, const KeyFrame &next, float progression)
{
	std::unordered_map<std::string, glm::mat4> currentPose;
	for (auto const&[jointName, previousTransform] : prev.getPose())
	{
		auto const &nextTransform = next.getPose().at(jointName);
		const JointTransform &currentTransform = JointTransform::interpolate(previousTransform, nextTransform,
																			 progression);
		currentPose[jointName] = currentTransform.getLocalTransform();
	}
	return currentPose;
}
