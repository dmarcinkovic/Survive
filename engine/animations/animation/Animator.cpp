//
// Created by david on 01. 10. 2020..
//

#include "Animator.h"

Animator::Animator(Animation animation, AnimatedModel animatedModel)
    : m_Animation(std::move(animation)), m_Model(std::move(animatedModel))
{

}

std::unordered_map<std::string, glm::mat4> Animator::calculatePose() const
{

}

void Animator::applyPoseToJoints(const std::unordered_map<std::string, glm::mat4> &currentPose, Joint &joint,
                                 const glm::mat4 &parentTransformation)
{
    glm::mat4 currentLocalTransform = currentPose.at(joint.name());
    glm::mat4 currentTransform = parentTransformation * currentLocalTransform;

    for (auto& child : joint.children())
    {
        applyPoseToJoints(currentPose, child, currentTransform);
    }

    currentTransform = currentTransform * joint.inverseBindTransform();
    joint.setAnimatedTransform(currentTransform);
}
