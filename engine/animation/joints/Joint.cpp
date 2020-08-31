//
// Created by david on 10. 06. 2020..
//

#include "Joint.h"

Joint::Joint(std::string name, int index, const glm::mat4 &bindLocalTransform)
    : m_Name(std::move(name)), m_Index(index), m_LocalBindTransform(bindLocalTransform)
{

}

void Joint::addChild(const Joint &childJoint)
{
    m_Children.emplace_back(childJoint);
}

void Joint::calculateInverseBindTransform(const glm::mat4 &parentBindTransform)
{
    auto bindTransform = parentBindTransform * m_LocalBindTransform;
    m_InverseBindTransformation = glm::inverse(bindTransform);

    for (auto &child :m_Children)
    {
        child.calculateInverseBindTransform(bindTransform);
    }
}
