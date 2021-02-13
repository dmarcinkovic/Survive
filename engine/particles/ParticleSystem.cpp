//
// Created by david on 13. 02. 2021..
//

#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(const TexturedModel &particleTexture, float particlesPerSecond, float speed,
							   float gravity, float lifeLength)
		: m_Texture(particleTexture), m_ParticlesPerSecond(particlesPerSecond), m_Speed(speed), m_Gravity(gravity),
		  m_LifeLength(lifeLength)
{

}
