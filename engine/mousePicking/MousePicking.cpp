//
// Created by david on 29. 12. 2020..
//

#include <iostream>

#include "MousePicking.h"
#include "../display/Display.h"
#include "../math/Maths.h"


MousePicking::MousePicking(const Camera &camera)
		: m_Camera(camera)
{
	mousePressedHandler();
}

void MousePicking::mousePressedHandler()
{
	Display::addMouseListener([this](int button, int action, double mouseX, double mouseY) {
		if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT)
		{
			glm::vec3 mouseRay = getMouseRay(mouseX, mouseY);

			std::cout << mouseRay.x << ' ' << mouseRay.y << ' ' << mouseRay.z << '\n';
		}
	});
}

glm::vec3 MousePicking::getNormalizedDeviceCoordinates(const glm::vec2 &viewportCoordinates)
{
	auto[width, height] = Display::getWindowSize<float>();

	float x = (2.0f * viewportCoordinates.x) / width - 1.0f;
	float y = 1.0f - (2.0f * viewportCoordinates.y) / height;

	return glm::vec3{x, y, 1.0f};
}

glm::vec4 MousePicking::getClipCoordinates(const glm::vec3 &normalizedDeviceCoordinates)
{
	return glm::vec4{normalizedDeviceCoordinates.x, normalizedDeviceCoordinates.y, -1.0f, 1.0f};
}

glm::vec4 MousePicking::getEyeCoordinates(const glm::vec4 &clipCoordinates)
{
	glm::vec4 eye = glm::inverse(Maths::projectionMatrix) * clipCoordinates;
	return glm::vec4{eye.x, eye.y, -1.0f, 0.0f};
}

glm::vec3 MousePicking::getWorldCoordinates(const glm::vec4 &eyeCoordinates, const Camera &camera)
{
	glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
	glm::vec4 world = glm::inverse(viewMatrix) * eyeCoordinates;

	return glm::normalize(glm::vec3{world});
}

glm::vec3 MousePicking::getMouseRay(double mouseX, double mouseY) const
{
	glm::vec2 viewportCoordinates{mouseX, mouseY};
	glm::vec3 normalizedDeviceCoordinates = getNormalizedDeviceCoordinates(viewportCoordinates);
	glm::vec4 clipCoordinates = getClipCoordinates(normalizedDeviceCoordinates);
	glm::vec4 eyeCoordinates = getEyeCoordinates(clipCoordinates);
	glm::vec3 worldCoordinates = getWorldCoordinates(eyeCoordinates, m_Camera);

	return worldCoordinates;
}
