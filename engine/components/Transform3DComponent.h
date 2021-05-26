//
// Created by david on 02. 03. 2021..
//

#ifndef SURVIVE_TRANSFORM3DCOMPONENT_H
#define SURVIVE_TRANSFORM3DCOMPONENT_H

#include <glm/glm.hpp>

namespace Survive
{
	struct Transform3DComponent
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		Transform3DComponent()
			: position{}, rotation{}, scale{1.0f}
		{
		}

		explicit Transform3DComponent(const glm::vec3 &position, const glm::vec3 &scale = glm::vec3{1.0f},
									  const glm::vec3 &rotation = glm::vec3{0.0f})
				: position(position), rotation(rotation), scale(scale)
		{}
	};
}

#endif //SURVIVE_TRANSFORM3DCOMPONENT_H
