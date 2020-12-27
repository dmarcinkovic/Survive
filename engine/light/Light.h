//
// Created by david on 17. 05. 2020..
//

#ifndef SURVIVE_LIGHT_H
#define SURVIVE_LIGHT_H

#include <glm/glm.hpp>

class Light
{
private:
	const glm::vec3 m_Position;
	const glm::vec3 m_Color;

public:
	Light(const glm::vec3 &position, const glm::vec3 &color);

	[[nodiscard]] const glm::vec3 &position() const;

	[[nodiscard]] const glm::vec3 &color() const;
};


#endif //SURVIVE_LIGHT_H
