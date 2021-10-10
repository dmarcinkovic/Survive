//
// Created by david on 17. 05. 2020..
//

#include "Display.h"
#include "Camera.h"
#include "Maths.h"

Survive::Camera::Camera()
{
	auto[width, height] = Display::getWindowSize<float>();

	m_ProjectionMatrix = Maths::createProjectionMatrix(fieldOfView, near, far, width, height);
	m_OrthographicProjectionMatrix = Maths::createOrthographicProjectionMatrix(width / height, 1.0f);
	m_LightProjectionMatrix = Maths::createLightProjectionMatrix(near, far);
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
	m_ProjectionMatrix = Maths::createProjectionMatrix(fieldOfView, near, far, width, height);
	m_OrthographicProjectionMatrix = Maths::createOrthographicProjectionMatrix(width / height, 1.0f);
}

glm::mat4 Survive::Camera::getOrthographicProjectionMatrix() const
{
	return m_OrthographicProjectionMatrix;
}

glm::mat4 Survive::Camera::getLightProjectionMatrix() const
{
	return m_LightProjectionMatrix;
}
