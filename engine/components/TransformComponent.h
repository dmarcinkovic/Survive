//
// Created by david on 02. 03. 2021..
//

#ifndef SURVIVE_TRANSFORMCOMPONENT_H
#define SURVIVE_TRANSFORMCOMPONENT_H

#include <glm/glm.hpp>

struct TransformComponent
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	TransformComponent() = default;

	explicit TransformComponent(const glm::vec3 &position, const glm::vec3 &scale = glm::vec3{1.0f},
								const glm::vec3 &rotation = glm::vec3{0.0f})
			: position(position), rotation(rotation), scale(scale)
	{}
};

#endif //SURVIVE_TRANSFORMCOMPONENT_H
