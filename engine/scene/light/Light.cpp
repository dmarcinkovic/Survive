//
// Created by david on 17. 05. 2020..
//

#include "Light.h"
#include "Maths.h"

Survive::Light::Light(const glm::vec3 &position, const glm::vec3 &color)
		: m_Position(position), m_Color(color)
{
}

const glm::vec3 &Survive::Light::position() const
{
	return m_Position;
}

const glm::vec3 &Survive::Light::color() const
{
	return m_Color;
}

glm::mat4 Survive::Light::getViewMatrix() const
{
	return Maths::createLightViewMatrix(m_Position);
}
