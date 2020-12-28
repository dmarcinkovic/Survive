//
// Created by david on 29. 12. 2020..
//

#include <iostream>

#include "MousePicking.h"
#include "../display/Display.h"


MousePicking::MousePicking()
{
	mousePressedHandler();
}

void MousePicking::mousePressedHandler()
{
	Display::addMouseListener([this](int button, int action, double mouseX, double mouseY) {
		if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT)
		{
			glm::vec2 viewportCoordinates{mouseX, mouseY};
			glm::vec2 normalizedDeviceCoordinates = getNormalizedDeviceCoordinates(viewportCoordinates);

			std::cout << "Mouse pressed: " << mouseX << ' ' << mouseY << '\n';
			std::cout << "X and Y: " << normalizedDeviceCoordinates.x << ' ' << normalizedDeviceCoordinates.y << '\n';
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
