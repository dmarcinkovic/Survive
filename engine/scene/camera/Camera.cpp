//
// Created by david on 17. 05. 2020..
//

#include "Display.h"
#include "Camera.h"
#include "Maths.h"

Survive::Camera::Camera()
{
	auto [width, height] = Display::getWindowSize<float>();

	m_ProjectionMatrix = Maths::createProjectionMatrix(fieldOfView, nearPlane, farPlane, width, height);
	m_OrthographicProjectionMatrix = Maths::createOrthographicProjectionMatrix(width / height, 1.0f);
	m_LightProjectionMatrix = Maths::createLightProjectionMatrix(nearPlane, farPlane);

	recalculateViewMatrix();
}

void Survive::Camera::invertPitch()
{
	m_Pitch = -m_Pitch;
}

void Survive::Camera::moveCameraInYDirection(float yDistance)
{
	m_Position.y += yDistance;
}

const glm::mat4 &Survive::Camera::getProjectionMatrix() const
{
	return m_ProjectionMatrix;
}

const glm::mat4 &Survive::Camera::getViewMatrix() const
{
	return m_ViewMatrix;
}

glm::mat4 &Survive::Camera::getViewMatrix()
{
	return m_ViewMatrix;
}

void Survive::Camera::recalculateProjectionMatrix(float width, float height)
{
	m_ProjectionMatrix = Maths::createProjectionMatrix(fieldOfView, nearPlane, farPlane, width, height);
	m_OrthographicProjectionMatrix = Maths::createOrthographicProjectionMatrix(width / height, 1.0f);
}

const glm::mat4 &Survive::Camera::getOrthographicProjectionMatrix() const
{
	return m_OrthographicProjectionMatrix;
}

const glm::mat4 &Survive::Camera::getLightProjectionMatrix() const
{
	return m_LightProjectionMatrix;
}

float Survive::Camera::getPitch() const
{
	return m_Pitch;
}

float Survive::Camera::getYaw() const
{
	return m_Yaw;
}

const glm::vec3 &Survive::Camera::getPosition() const
{
	return m_Position;
}

void Survive::Camera::setPitch(float pitch)
{
	m_Pitch = pitch;
	recalculateViewMatrix();
}

void Survive::Camera::setYaw(float yaw)
{
	m_Yaw = yaw;
	recalculateViewMatrix();
}

void Survive::Camera::setPosition(const glm::vec3 &position)
{
	m_Position = position;
	recalculateViewMatrix();
}

void Survive::Camera::setCameraProperties(float pitch, float yaw, const glm::vec3 &position)
{
	m_Pitch = pitch;
	m_Yaw = yaw;
	m_Position = position;
}

void Survive::Camera::recalculateViewMatrix()
{
	m_ViewMatrix = Maths::createViewMatrix(m_Pitch, m_Yaw, m_Position);
}
