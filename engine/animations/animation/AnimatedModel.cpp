//
// Created by david on 01. 10. 2020..
//

#include "AnimatedModel.h"

#include <utility>

AnimatedModel::AnimatedModel(Joint rootJoint, int numberOfJoints, const TexturedModel &texture,
                             const glm::vec3 &position, const glm::vec3 &rotation, bool isTransparent, float scaleX,
                             float scaleY, float scaleZ)
        : Object3D(texture, position, rotation, isTransparent, scaleX, scaleY, scaleZ),
          m_RootJoint(std::move(rootJoint)), m_NumberOfJoints(numberOfJoints)
{
    m_RootJoint.calculateInverseBindTransform(glm::mat4{1});
}

Joint &AnimatedModel::rootJoint()
{
    return m_RootJoint;
}
