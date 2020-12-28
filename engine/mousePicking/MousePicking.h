//
// Created by david on 29. 12. 2020..
//

#ifndef SURVIVE_MOUSEPICKING_H
#define SURVIVE_MOUSEPICKING_H

#include <glm/glm.hpp>

class MousePicking
{
public:
	MousePicking();

private:
	void mousePressedHandler();

	static glm::vec3 getNormalizedDeviceCoordinates(const glm::vec2& viewportCoordinates);

	static glm::vec4 getClipCoordinates(const glm::vec3 &normalizedDeviceCoordinates);
};


#endif //SURVIVE_MOUSEPICKING_H
