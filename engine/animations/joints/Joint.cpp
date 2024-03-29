//
// Created by david on 10. 06. 2020..
//

#include "Joint.h"

Survive::Joint::Joint(std::string name, size_t index, const glm::mat4 &bindLocalTransform)
		: m_Name(std::move(name)), m_Index(index), m_LocalBindTransform(glm::transpose(bindLocalTransform))
{
}

void Survive::Joint::addChild(const Joint &childJoint)
{
	m_Children.emplace_back(childJoint);
}

void Survive::Joint::calculateInverseBindTransform(const glm::mat4 &parentBindTransform)
{
	auto bindTransform = parentBindTransform * m_LocalBindTransform;
	m_InverseBindTransformation = glm::inverse(bindTransform);

	for (auto &child : m_Children)
	{
		child.calculateInverseBindTransform(bindTransform);
	}
}

std::vector<Survive::Joint> &Survive::Joint::children()
{
	return m_Children;
}

const std::string &Survive::Joint::name() const
{
	return m_Name;
}

const glm::mat4 &Survive::Joint::inverseBindTransform() const
{
	return m_InverseBindTransformation;
}

void Survive::Joint::setAnimatedTransform(const glm::mat4 &animatedTransform)
{
	m_AnimatedTransform = animatedTransform;
}

size_t Survive::Joint::index() const
{
	return m_Index;
}

const glm::mat4 &Survive::Joint::getAnimatedTransform() const
{
	return m_AnimatedTransform;
}

const std::vector<Survive::Joint> &Survive::Joint::children() const
{
	return m_Children;
}

void Survive::Joint::applyCorrection(const glm::mat4 &correction)
{
	m_LocalBindTransform = correction * m_LocalBindTransform;
}