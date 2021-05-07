//
// Created by david on 17. 05. 2020..
//

#include "Light.h"

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
