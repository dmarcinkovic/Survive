//
// Created by david on 17. 05. 2020..
//

#ifndef SURVIVE_LIGHT_H
#define SURVIVE_LIGHT_H

#include <glm/glm.hpp>

namespace Survive
{
	class Light
	{
	private:
		const glm::vec3 m_Position;
		const glm::vec3 m_Color;

		glm::mat4 m_LightProjectionMatrix{};

	public:
		Light(const glm::vec3 &position, const glm::vec3 &color);

		[[nodiscard]] const glm::vec3 &position() const;

		[[nodiscard]] const glm::vec3 &color() const;

		[[nodiscard]] glm::mat4 getProjectionMatrix() const;

		[[nodiscard]] glm::mat4 getViewMatrix() const;
	};
}

#endif //SURVIVE_LIGHT_H
