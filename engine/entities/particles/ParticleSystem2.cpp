//
// Created by david on 25.05.22..
//

#include "ParticleSystem2.h"
#include "Util.h"
#include "Transform3DComponent.h"
#include "Display.h"

void Survive::ParticleSystem2::update(entt::registry &registry)
{
	auto entities = registry.view<ParticleComponent, Transform3DComponent>();

	for (auto const &entity: entities)
	{
		ParticleComponent &particleComponent = entities.get<ParticleComponent>(entity);
		const Transform3DComponent &transform = entities.get<Transform3DComponent>(entity);

		generateParticles(transform.position, particleComponent);
		updateParticles(particleComponent.m_Particles, particleComponent.gravity, particleComponent.lifeLength);
	}
}

void Survive::ParticleSystem2::emitParticle(const glm::vec3 &center, ParticleComponent &particleComponent)
{
	// TODO: do not hardcode these values
	float dirX = Util::getRandom(0, 2.0f) - 1.0f;
	float dirZ = Util::getRandom(0, 2.0f) - 1.0f;

	glm::vec3 velocity{dirX, 1, dirZ};
	velocity = glm::normalize(velocity) * particleComponent.speed;

	Particle2 particle{};
	particle.position = center;
	particle.velocity = velocity;
	particle.scale = glm::vec3{0.2f};

	// TODO: update this when particle system get more complicated: e.g. scale, scale error, etc.
	particleComponent.m_Particles.emplace_back(particle);
}

void Survive::ParticleSystem2::generateParticles(const glm::vec3 &center, ParticleComponent &particleComponent)
{
	auto frameTime = static_cast<float>(Display::getFrameTime());
	float particlesToCreate = particleComponent.particlesPerSecond * frameTime;
	int count = std::floor(particlesToCreate);

	for (int i = 0; i < count; ++i)
	{
		emitParticle(center, particleComponent);
	}

	float partialParticle = std::fmod(particlesToCreate, 1.0f);
	if (Util::getRandom(0.0f, 1.0f) < partialParticle)
	{
		emitParticle(center, particleComponent);
	}
}

bool Survive::ParticleSystem2::updateParticle(Particle2 &particle, float gravity, float lifeLength)
{
	auto frameTime = static_cast<float>(Display::getFrameTime());

	particle.velocity.y += frameTime * gravity;
	particle.position += frameTime * particle.velocity;

	// TODO: update texture cord info if sprite sheet component is attached to this entity
	particle.elapsedTime += frameTime;

	return particle.elapsedTime < lifeLength;
}

void Survive::ParticleSystem2::updateParticles(std::vector<Particle2> &particles, float gravity, float lifeLength)
{
	particles.erase(std::remove_if(particles.begin(), particles.end(), [&](Particle2 &particle) {
		return !updateParticle(particle, gravity, lifeLength);
	}), particles.end());
}
