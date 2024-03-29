//
// Created by david on 01. 10. 2020..
//

#include "Animator.h"
#include "Display.h"

Survive::Animator::Animator(Animation animation)
		: m_Animation(std::move(animation))
{

}

std::unordered_map<std::string, glm::mat4> Survive::Animator::calculatePose() const
{
	auto[prev, next] = nextAndPreviousFrames();
	float progression = calculateProgression(prev, next);

	return interpolatePoses(prev, next, progression);
}

void Survive::Animator::applyPoseToJoints(const std::unordered_map<std::string, glm::mat4> &currentPose, Joint &joint,
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

void Survive::Animator::update(Joint &rootJoint)
{
	increaseAnimationTime();
	std::unordered_map<std::string, glm::mat4> currentPose = calculatePose();
	applyPoseToJoints(currentPose, rootJoint, glm::mat4{1});
}

void Survive::Animator::increaseAnimationTime()
{
	m_AnimationTime += static_cast<float>(Display::getFrameTime());
	if (m_AnimationTime > m_Animation.getLength())
	{
		m_AnimationTime = std::fmod(m_AnimationTime, m_Animation.getLength());
	}
}

std::pair<Survive::KeyFrame, Survive::KeyFrame> Survive::Animator::nextAndPreviousFrames() const
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

float Survive::Animator::calculateProgression(const KeyFrame &prev, const KeyFrame &next) const
{
	float totalTime = next.timeStamp() - prev.timeStamp();
	float currentTime = m_AnimationTime - prev.timeStamp();
	return currentTime / totalTime;
}

std::unordered_map<std::string, glm::mat4>
Survive::Animator::interpolatePoses(const KeyFrame &prev, const KeyFrame &next, float progression)
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
