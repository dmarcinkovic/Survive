//
// Created by david on 05. 03. 2021..
//

#ifndef SURVIVE_TRANSFORM2DCOMPONENT_H
#define SURVIVE_TRANSFORM2DCOMPONENT_H

#include <glm/glm.hpp>

struct Transform2DComponent
{
	glm::vec2 position;
	glm::vec2 rotation;
	glm::vec2 scale;

	Transform2DComponent() = default;

	explicit Transform2DComponent(const glm::vec2 &position, const glm::vec2 &scale = glm::vec2{1.0f},
								  const glm::vec2 &rotation = glm::vec2{0.0f})
			: position(position), rotation(rotation), scale(scale)
	{}
};

#endif //SURVIVE_TRANSFORM2DCOMPONENT_H
