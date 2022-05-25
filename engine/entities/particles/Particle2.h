//
// Created by david on 23.05.22..
//

#ifndef SURVIVE_PARTICLE2_H
#define SURVIVE_PARTICLE2_H

#include <glm/glm.hpp>

namespace Survive
{
	struct Particle2
	{
		glm::vec3 position;
		glm::vec3 scale{1.0f};
		glm::vec3 velocity{};
		float elapsedTime{};
	};
}


#endif //SURVIVE_PARTICLE2_H
