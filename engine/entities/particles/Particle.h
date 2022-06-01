//
// Created by david on 23.05.22..
//

#ifndef SURVIVE_PARTICLE_H
#define SURVIVE_PARTICLE_H

#include <glm/glm.hpp>

#include "SpriteSheetComponent.h"

namespace Survive
{
	struct Particle
	{
		glm::vec3 position;
		glm::vec3 scale{1.0f};
		glm::vec3 velocity{};

		float elapsedTime{};
		SpriteSheetComponent sprite;
	};
}


#endif //SURVIVE_PARTICLE_H
