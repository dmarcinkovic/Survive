//
// Created by david on 13. 02. 2021..
//

#include "ParticleSystem.h"
#include "../display/Display.h"

ParticleSystem::ParticleSystem(const TexturedModel &particleTexture, float particlesPerSecond, float speed,
							   float gravity, float lifeLength)
		: m_Texture(particleTexture), m_ParticlesPerSecond(particlesPerSecond), m_Speed(speed), m_Gravity(gravity),
		  m_LifeLength(lifeLength)
{

}

void ParticleSystem::generateParticles(const glm::vec3 &systemCenter, std::vector<Particle> &particles)
{
	auto deltaTime = static_cast<float>(Display::getFrameTime());
	float particlesToCreate = m_ParticlesPerSecond * deltaTime;

	int count = static_cast<int>(std::round(particlesToCreate));

	for (int i = 0; i < count; ++i)
	{
		emitParticle(systemCenter, particles);
	}
}

void ParticleSystem::emitParticle(const glm::vec3 &center, std::vector<Particle> &particles)
{

}
