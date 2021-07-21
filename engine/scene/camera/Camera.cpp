//
// Created by david on 17. 05. 2020..
//

#include <Display.h>
#include "Camera.h"
#include "Maths.h"
#include "Constants.h"

Survive::Camera::Camera()
		: m_ProjectionMatrix(Maths::createProjectionMatrix(Constants::FOV))
{
	addWindowResizeHandler();
}

void Survive::Camera::invertPitch()
{
	pitch = -pitch;
}

void Survive::Camera::moveCameraInYDirection(float yDistance)
{
	position.y += yDistance;
}

void Survive::Camera::addWindowResizeHandler()
{
	auto windowResizeListener = [this](int, int) {
		m_ProjectionMatrix = Maths::createProjectionMatrix(Constants::FOV);
	};

	Display::addWindowResizeListener(windowResizeListener);
}

glm::mat4 Survive::Camera::getProjectionMatrix() const
{
	return m_ProjectionMatrix;
}
