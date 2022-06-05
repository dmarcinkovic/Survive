//
// Created by david on 25.05.22..
//

#include "ParticleSystem.h"
#include "Util.h"
#include "Transform3DComponent.h"
#include "Display.h"
#include "SpriteSheetComponent.h"
#include "SpriteUpdate.h"

void Survive::ParticleSystem::update(entt::registry &registry)
{
	auto entities = registry.view<ParticleComponent, Transform3DComponent>();

	for (auto const &entity: entities)
	{
		ParticleComponent &particleComponent = entities.get<ParticleComponent>(entity);
		const Transform3DComponent &transform = entities.get<Transform3DComponent>(entity);

		generateParticles(registry, entity, transform.position, transform.scale, particleComponent);

		float gravity = particleComponent.gravity;
		float lifeLength = particleComponent.lifeLength;
		float lifeError = Util::getRandom(-particleComponent.lifeError, particleComponent.lifeError);

		updateParticleSprite(registry, entity, particleComponent.m_Particles);
		updateParticles(particleComponent.m_Particles, gravity, lifeLength, lifeError);
	}
}

void Survive::ParticleSystem::emitParticle(const entt::registry &registry, entt::entity entity, const glm::vec3 &center,
										   const glm::vec3 &scale, ParticleComponent &particleComponent)
{
	float deviation = particleComponent.directionDeviation;
	float dirX = Util::getRandom(-deviation, deviation);
	float dirZ = Util::getRandom(-deviation, deviation);

	glm::vec3 velocity{dirX, 1, dirZ};
	float speedError = Util::getRandom(-particleComponent.speedError, particleComponent.speedError);
	velocity = glm::normalize(velocity) * (particleComponent.speed + speedError);

	Particle particle{};
	particle.position = center;
	particle.velocity = velocity;
	particle.scale = scale + Util::getRandom(-particleComponent.scaleError, particleComponent.scaleError);

	initializeParticleSprite(registry, entity, particle);
	particleComponent.m_Particles.emplace_back(particle);
}

void Survive::ParticleSystem::generateParticles(const entt::registry &registry, entt::entity entity,
												const glm::vec3 &center, const glm::vec3 &scale,
												ParticleComponent &particleComponent)
{
	auto frameTime = static_cast<float>(Display::getFrameTime());
	float particlesToCreate = particleComponent.particlesPerSecond * frameTime;
	int count = std::floor(particlesToCreate);

	for (int i = 0; i < count; ++i)
	{
		emitParticle(registry, entity, center, scale, particleComponent);
	}

	float partialParticle = std::fmod(particlesToCreate, 1.0f);
	if (Util::getRandom(0.0f, 1.0f) < partialParticle)
	{
		emitParticle(registry, entity, center, scale, particleComponent);
	}
}

bool Survive::ParticleSystem::updateParticle(Particle &particle, float gravity, float lifeLength, float lifeError)
{
	auto frameTime = static_cast<float>(Display::getFrameTime());

	particle.velocity.y += frameTime * gravity;
	particle.position += frameTime * particle.velocity;
	particle.elapsedTime += frameTime;

	return particle.elapsedTime < lifeLength + lifeError;
}

void Survive::ParticleSystem::updateParticles(std::vector<Particle> &particles, float gravity, float lifeLength,
											  float lifeError)
{
	particles.erase(std::remove_if(particles.begin(), particles.end(), [&](Particle &particle) {
		return !updateParticle(particle, gravity, lifeLength, lifeError);
	}), particles.end());
}

void Survive::ParticleSystem::updateParticleSprite(const entt::registry &registry, entt::entity entity,
												   std::vector<Particle> &particles)
{
	if (registry.any_of<SpriteSheetComponent>(entity))
	{
		const SpriteSheetComponent &spriteSheet = registry.get<SpriteSheetComponent>(entity);
		if (spriteSheet.animating)
		{
			for (Particle &particle: particles)
			{
				SpriteUpdate::updateSprite(particle.sprite);
			}
		}
	}
}

void Survive::ParticleSystem::initializeParticleSprite(const entt::registry &registry, entt::entity entity,
													   Survive::Particle &particle)
{
	if (registry.any_of<SpriteSheetComponent>(entity))
	{
		SpriteSheetComponent &sprite = particle.sprite;

		sprite = registry.get<SpriteSheetComponent>(entity);
		sprite.m_Time = 0;
		sprite.m_CurrentEpoch = 0;
		sprite.m_PreviousFrameIndex = 0;
		sprite.currentFrameIndex = sprite.m_InitialFrameIndex;
	}
}
