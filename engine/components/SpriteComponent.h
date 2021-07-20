//
// Created by david on 04. 03. 2021..
//

#ifndef SURVIVE_SPRITECOMPONENT_H
#define SURVIVE_SPRITECOMPONENT_H

#include <glm/glm.hpp>

namespace Survive
{
	struct SpriteComponent
	{
		glm::vec4 color;

		explicit SpriteComponent(const glm::vec4 &color)
				: color(color)
		{}

		SpriteComponent() = default;
	};
}

#endif //SURVIVE_SPRITECOMPONENT_H
