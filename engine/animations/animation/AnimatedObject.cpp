//
// Created by david on 01. 10. 2020..
//

#include "AnimatedObject.h"

#include <iostream>

AnimatedObject::AnimatedObject(Joint &rootJoint, int numberOfJoints, const TexturedModel &texture,
                               const glm::vec3 &position, const glm::vec3 &rotation, bool isTransparent, float scaleX,
                               float scaleY, float scaleZ)
        : Object3D(texture, position, rotation, isTransparent, scaleX, scaleY, scaleZ),
          m_RootJoint(rootJoint), m_NumberOfJoints(numberOfJoints)
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

//    for (int k = 0; k < 4; ++k)
//    {
//        for (const auto &transform : jointMatrices)
//        {
//            for (int j = 0; j < 4; ++j)
//            {
//                std::cout << transform[k][j] << ' ';
//            }
//            std::cout << "  ";
//        }
//        std::cout << '\n';
//    }
//    std::cout << '\n';

    return jointMatrices;
}

void AnimatedObject::addJointsToArray(const Joint &headJoint, std::vector<glm::mat4> &jointMatrices) const
{
    jointMatrices[headJoint.index()] = headJoint.getAnimatedTransform();

//    for (int i = 0; i < 4; ++i)
//    {
//        for (int j = 0; j < 4; ++j)
//        {
//            std::cout << headJoint.getAnimatedTransform()[i][j] << ' ';
//        }
//        std::cout << '\n';
//    }
//    std::cout << '\n';

    for (auto const &childJoint : headJoint.children())
    {
        addJointsToArray(childJoint, jointMatrices);
    }
}
