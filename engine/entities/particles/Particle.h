//
// Created by david on 23.05.22..
//

#ifndef SURVIVE_PARTICLE_H
#define SURVIVE_PARTICLE_H

#include <glm/glm.hpp>

namespace Survive
{
	struct Particle
	{
		glm::vec3 position;
		glm::vec3 scale{1.0f};
		glm::vec3 velocity{};

		float elapsedTime{};
	};
}


#endif //SURVIVE_PARTICLE_H
