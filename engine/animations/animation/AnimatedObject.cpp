//
// Created by david on 01. 10. 2020..
//

#include "AnimatedObject.h"

#include <utility>

AnimatedObject::AnimatedObject(Joint rootJoint, int numberOfJoints, const TexturedModel &texture,
                               const glm::vec3 &position, const glm::vec3 &rotation, bool isTransparent, float scaleX,
                               float scaleY, float scaleZ)
        : Object3D(texture, position, rotation, isTransparent, scaleX, scaleY, scaleZ),
          m_RootJoint(std::move(rootJoint)), m_NumberOfJoints(numberOfJoints)
{
    m_RootJoint.calculateInverseBindTransform(glm::mat4{1});
}

Joint &AnimatedObject::rootJoint()
{
    return m_RootJoint;
}

std::vector<glm::mat4> AnimatedObject::getJointTransforms() const
{
    std::vector<glm::mat4> jointMatrices(m_NumberOfJoints);
    addJointsToArray(m_RootJoint, jointMatrices);

    return jointMatrices;
}

void AnimatedObject::addJointsToArray(const Joint &headJoint, std::vector<glm::mat4> &jointMatrices) const
{
    jointMatrices[headJoint.index()] = headJoint.getAnimatedTransform();
    for (auto const& childJoint : headJoint.children())
    {
        addJointsToArray(childJoint, jointMatrices);
    }
}
