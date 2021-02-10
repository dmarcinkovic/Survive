//
// Created by david on 05. 02. 2021..
//

#include "Particle.h"

Particle::Particle(const TexturedModel &particleTexture, int rows, const glm::vec3 &position, const glm::vec3 &velocity,
				   float gravityEffect, float lifeLength, float rotation, float scale)
		: Entity(particleTexture, position, glm::vec3{scale, scale, scale}), m_Rows(rows), m_Velocity(velocity),
		  m_GravityEffect(gravityEffect), m_LifeLength(lifeLength), m_Rotation(rotation)
{

}

bool Particle::update(const Camera &camera)
{
	return false;
}

void Particle::updateTextureCoordInfo()
{

}

void Particle::setTextureOffset(int index) const
{

}
