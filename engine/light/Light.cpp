//
// Created by david on 17. 05. 2020..
//

#include "Light.h"

Light::Light(const glm::vec3 &position, const glm::vec3 &color)
		: m_Position(position), m_Color(color)
{

}

const glm::vec3 &Light::position() const
{
	return m_Position;
}

const glm::vec3 &Light::color() const
{
	return m_Color;
}
