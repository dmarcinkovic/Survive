//
// Created by david on 17. 05. 2020..
//

#include "../display/Display.h"
#include "Camera.h"

Camera::Camera()
{
	addScrollListener();
	addMousePressedListener();
	addMouseMovedListener();
	addKeyboardListener();
}

void Camera::addScrollListener()
{
	auto scrollListener = [this](double xOffset, double yOffset) {
		m_Position.z -= yOffset * 2.0;
	};
	Display::addScrollListener(scrollListener);
}

void Camera::addMousePressedListener()
{
	auto mousePressedListener = [this](int button, int action, double mouseX, double mouseY) {
		if (action == GLFW_PRESS)
		{
			if (button == GLFW_MOUSE_BUTTON_RIGHT)
			{
				m_RightButtonPressed = true;
			} else
			{
				m_LeftButtonPressed = true;
			}

			m_MousePos = glm::vec2{mouseX, mouseY};
			m_CurrentRotation = m_Rotation;
			m_CurrentPitch = m_Pitch;
			m_CurrentYaw = m_Yaw;
		} else
		{
			m_LeftButtonPressed = false;
			m_RightButtonPressed = false;
		}
	};
	Display::addMouseListener(mousePressedListener);
}

void Camera::addMouseMovedListener()
{
	auto mouseMovedListener = [this](double mouseX, double mouseY) {
		double dy = mouseY - m_MousePos.y;
		double dx = mouseX - m_MousePos.x;

		if (m_LeftButtonPressed)
		{
			m_Rotation.y = m_CurrentRotation.y + dx / 2.0;
			m_Rotation.x = m_CurrentRotation.x + dy / 2.0;
		} else if (m_RightButtonPressed)
		{
			m_Pitch = m_CurrentPitch + static_cast<float >(dy / 5.0);
			m_Yaw = m_CurrentYaw + static_cast<float >(dx / 5.0);
		}
	};
	Display::addMouseMovedListener(mouseMovedListener);
}

void Camera::addKeyboardListener()
{
	auto keyboardListener = [this](int key, int action) {
		if (action == GLFW_PRESS)
		{
			switch (key)
			{
				case GLFW_KEY_LEFT :
					m_Position.x -= 3.0;
					break;
				case GLFW_KEY_RIGHT :
					m_Position.x += 3.0;
					break;
				case GLFW_KEY_DOWN :
					m_Position.y -= 3.0;
					break;
				case GLFW_KEY_UP :
					m_Position.y += 3.0;
					break;
				default:
					break;
			}
		}
	};
	Display::addKeyListener(keyboardListener);
}

void Camera::invertPitch()
{
	m_Pitch = -m_Pitch;
}

void Camera::moveCameraInYDirection(float yDistance)
{
	m_Position.y += yDistance;
}
