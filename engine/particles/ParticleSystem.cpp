//
// Created by david on 13. 02. 2021..
//

#include "ParticleSystem.h"
#include "../display/Display.h"
#include "../math/Maths.h"

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
	float dirX = Maths::getRandom(0, 1) * 1.2f - 1.0f;
	float dirZ = Maths::getRandom(0, 1) * 1.2f - 1.0f;

	glm::vec3 velocity{dirX, 1.0f, dirZ};
	velocity = glm::normalize(velocity) * m_Speed;

	// TODO do not hardcode the number of rows in texture
	particles.emplace_back(Particle(m_Texture, 4, center, velocity, m_Gravity, m_LifeLength));
}
