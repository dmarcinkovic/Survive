//
// Created by david on 01. 10. 2020..
//

#include <iostream>
#include "Animator.h"
#include "../../display/Display.h"

Animator::Animator(Animation animation, AnimatedObject animatedObject)
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

//    std::cout << joint.name() << '\n';

//    std::cout << "Current local transform\n";
//    for (int i = 0; i < 4; ++i)
//    {
//        for (int j = 0; j < 4; ++j)
//        {
//            std::cout << currentLocalTransform[i][j] << ' ';
//        }
//        std::cout << '\n';
//    }
//    std::cout << '\n';
//
//    std::cout << "Parent transformation\n";
//    for (int i = 0; i < 4; ++i)
//    {
//        for (int j = 0; j < 4; ++j)
//        {
//            std::cout << parentTransformation[i][j] << ' ';
//        }
//        std::cout << '\n';
//    }
//    std::cout << '\n';
//
//    std::cout << "Current transform\n";
//    for (int i = 0; i < 4; ++i)
//    {
//        for (int j = 0; j < 4; ++j)
//        {
//            std::cout << currentTransform[i][j] << ' ';
//        }
//        std::cout << '\n';
//    }
//    std::cout << '\n';

    for (auto &child : joint.children())
    {
        applyPoseToJoints(currentPose, child, currentTransform);
    }

    currentTransform *= joint.inverseBindTransform();
    joint.setAnimatedTransform(currentTransform);
}

void Animator::update()
{
    increaseAnimationTime();
    std::unordered_map<std::string, glm::mat4> currentPose = calculatePose();
//    std::cout << "Update method\n";
    for (auto const&[name, pose]: currentPose)
    {
//        std::cout << name << '\n';
//        for (int i = 0; i <4; ++i)
//        {
//            for (int j = 0; j < 4; ++j)
//            {
//                std::cout << pose[i][j] << ' ';
//            }
//            std::cout << '\n';
//        }
//        std::cout << '\n';
    }
    applyPoseToJoints(currentPose, m_Model.rootJoint(), glm::mat4{1});
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
//	std::cout << "Interpolate poses\n";
	std::unordered_map<std::string, glm::mat4> currentPose;
	for (auto const&[jointName, previousTransform] : prev.getPose())
    {
		auto const &nextTransform = next.getPose().at(jointName);

//		std::cout << "Joint name: " << jointName << '\n';
//		std::cout << "Next transform\n";
//		auto localTransform = nextTransform.getLocalTransform();
//		for (int i = 0; i < 4; ++i)
//		{
//			for (int j = 0; j < 4; ++j)
//			{
//				std::cout << localTransform[i][j] << ' ';
//			}
//			std::cout << '\n';
//		}
//		std::cout << '\n';

        const JointTransform &currentTransform = JointTransform::interpolate(previousTransform, nextTransform,
                                                                             progression);


        currentPose[jointName] = currentTransform.getLocalTransform();
    }
    return currentPose;
}
