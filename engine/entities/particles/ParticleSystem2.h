//
// Created by david on 25.05.22..
//

#ifndef SURVIVE_PARTICLESYSTEM2_H
#define SURVIVE_PARTICLESYSTEM2_H

#include <glm/glm.hpp>

#include "entt.hpp"
#include "Particle2.h"
#include "ParticleComponent.h"

namespace Survive
{
	class ParticleSystem2
	{
	public:
		static void update(entt::registry &registry);

	private:
		static void emitParticle(const glm::vec3 &center, ParticleComponent &particleComponent);

		static void generateParticles(const glm::vec3 &center, ParticleComponent &particleComponent);

		static bool updateParticle(Particle2 &particle, float gravity, float lifeLength);

		static void updateParticles(std::vector<Particle2> &particles, float gravity, float lifeLength);
	};
}

#endif //SURVIVE_PARTICLESYSTEM2_H
