//
// Created by david on 25.05.22..
//

#include "ParticleSystem.h"
#include "Util.h"
#include "Transform3DComponent.h"
#include "Display.h"

void Survive::ParticleSystem::update(entt::registry &registry)
{
	auto entities = registry.view<ParticleComponent, Transform3DComponent>();

	for (auto const &entity: entities)
	{
		ParticleComponent &particleComponent = entities.get<ParticleComponent>(entity);
		const Transform3DComponent &transform = entities.get<Transform3DComponent>(entity);

		generateParticles(transform.position, transform.scale, particleComponent);
		updateParticles(particleComponent.m_Particles, particleComponent.gravity, particleComponent.lifeLength);
	}
}

void Survive::ParticleSystem::emitParticle(const glm::vec3 &center, const glm::vec3 &scale,
										   ParticleComponent &particleComponent)
{
	// TODO: do not hardcode these values
	float dirX = Util::getRandom(0, 2.0f) - 1.0f;
	float dirZ = Util::getRandom(0, 2.0f) - 1.0f;

	glm::vec3 velocity{dirX, 1, dirZ};
	velocity = glm::normalize(velocity) * particleComponent.speed;

	Particle particle{};
	particle.position = center;
	particle.velocity = velocity;
	// TODO: make scale equal to transform3Dcomponent scale
	particle.scale = scale;

	// TODO: update this when particle system get more complicated: e.g. scale, scale error, etc.
	particleComponent.m_Particles.emplace_back(particle);
}

void Survive::ParticleSystem::generateParticles(const glm::vec3 &center, const glm::vec3 &scale,
												ParticleComponent &particleComponent)
{
	auto frameTime = static_cast<float>(Display::getFrameTime());
	float particlesToCreate = particleComponent.particlesPerSecond * frameTime;
	int count = std::floor(particlesToCreate);

	for (int i = 0; i < count; ++i)
	{
		emitParticle(center, scale, particleComponent);
	}

	float partialParticle = std::fmod(particlesToCreate, 1.0f);
	if (Util::getRandom(0.0f, 1.0f) < partialParticle)
	{
		emitParticle(center, scale, particleComponent);
	}
}

bool Survive::ParticleSystem::updateParticle(Particle &particle, float gravity, float lifeLength)
{
	auto frameTime = static_cast<float>(Display::getFrameTime());

	particle.velocity.y += frameTime * gravity;
	particle.position += frameTime * particle.velocity;
	particle.elapsedTime += frameTime;

	return particle.elapsedTime < lifeLength;
}

void Survive::ParticleSystem::updateParticles(std::vector<Particle> &particles, float gravity, float lifeLength)
{
	particles.erase(std::remove_if(particles.begin(), particles.end(), [&](Particle &particle) {
		return !updateParticle(particle, gravity, lifeLength);
	}), particles.end());
}
