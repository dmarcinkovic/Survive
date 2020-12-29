//
// Created by david on 29. 12. 2020..
//

#ifndef SURVIVE_MOUSEPICKING_H
#define SURVIVE_MOUSEPICKING_H

#include <glm/glm.hpp>
#include "../camera/Camera.h"

class MousePicking
{
private:
	const Camera &m_Camera;

public:
	explicit MousePicking(const Camera &camera);

private:
	void mousePressedHandler();

	static glm::vec3 getNormalizedDeviceCoordinates(const glm::vec2 &viewportCoordinates);

	static glm::vec4 getClipCoordinates(const glm::vec3 &normalizedDeviceCoordinates);

	static glm::vec4 getEyeCoordinates(const glm::vec4 &clipCoordinates);

	static glm::vec3 getWorldCoordinates(const glm::vec4 &eyeCoordinates, const Camera &camera);
};


#endif //SURVIVE_MOUSEPICKING_H
