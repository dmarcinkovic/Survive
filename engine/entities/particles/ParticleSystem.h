//
// Created by david on 25.05.22..
//

#ifndef SURVIVE_PARTICLESYSTEM_H
#define SURVIVE_PARTICLESYSTEM_H

#include <glm/glm.hpp>

#include "entt.hpp"
#include "Particle.h"
#include "ParticleComponent.h"

namespace Survive
{
	class ParticleSystem
	{
	public:
		static void update(entt::registry &registry);

	private:
		static void emitParticle(const glm::vec3 &center, const glm::vec3 &scale, ParticleComponent &particleComponent);

		static void generateParticles(const glm::vec3 &center, const glm::vec3 &scale,
									  ParticleComponent &particleComponent);

		static bool updateParticle(Particle &particle, float gravity, float lifeLength, float lifeError);

		static void updateParticles(std::vector<Particle> &particles, float gravity, float lifeLength, float lifeError);
	};
}

#endif //SURVIVE_PARTICLESYSTEM_H
