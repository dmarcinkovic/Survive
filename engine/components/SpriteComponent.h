//
// Created by david on 04. 03. 2021..
//

#ifndef SURVIVE_SPRITECOMPONENT_H
#define SURVIVE_SPRITECOMPONENT_H

#include <glm/glm.hpp>

struct SpriteComponent
{
	glm::vec3 color;

	explicit SpriteComponent(const glm::vec3 &color)
			: color(color)
	{}
};

#endif //SURVIVE_SPRITECOMPONENT_H
