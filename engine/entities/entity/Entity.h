//
// Created by david on 27. 03. 2020..
//

#ifndef SURVIVE_ENTITY_H
#define SURVIVE_ENTITY_H

#include <glm/vec3.hpp>

#include "../../core/texture/TexturedModel.h"

namespace Survive
{
	struct Entity
	{
		TexturedModel m_Texture;
		glm::vec3 m_Position{};
		glm::vec3 m_Scale{};

		Entity(const TexturedModel &texture, const glm::vec3 &position,
			   const glm::vec3 &scale = glm::vec3{1.0f, 1.0f, 1.0f});

		Entity() = default;
	};
}


#endif //SURVIVE_ENTITY_H
