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

std::vector<Joint> &Joint::children()
{
	return m_Children;
}

const std::string &Joint::name() const
{
	return m_Name;
}

const glm::mat4 &Joint::inverseBindTransform() const
{
	return m_InverseBindTransformation;
}

void Joint::setAnimatedTransform(const glm::mat4 &animatedTransform)
{
	m_AnimatedTransform = animatedTransform;
}

int Joint::index() const
{
	return m_Index;
}

const glm::mat4 &Joint::getAnimatedTransform() const
{
	return m_AnimatedTransform;
}

const std::vector<Joint> &Joint::children() const
{
	return m_Children;
}
