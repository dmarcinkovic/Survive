//
// Created by david on 17. 05. 2020..
//

#include "Display.h"
#include "Camera.h"
#include "Maths.h"
#include "Constants.h"

Survive::Camera::Camera()
{
	auto[width, height] = Display::getWindowSize<float>();
	m_ProjectionMatrix = Maths::createProjectionMatrix(Constants::FOV, width, height);
}

void Survive::Camera::invertPitch()
{
	pitch = -pitch;
}

void Survive::Camera::moveCameraInYDirection(float yDistance)
{
	position.y += yDistance;
}

glm::mat4 Survive::Camera::getProjectionMatrix() const
{
	return m_ProjectionMatrix;
}

glm::mat4 Survive::Camera::getViewMatrix() const
{
	return Maths::createViewMatrix(pitch, yaw, position);
}

void Survive::Camera::recalculateProjectionMatrix(float width, float height)
{
	m_ProjectionMatrix = Maths::createProjectionMatrix(Constants::FOV, width, height);
}
