//
// Created by david on 17. 05. 2020..
//

#include "Camera.h"
#include "Display.h"

Survive::Camera::Camera()
{
	addScrollListener();
	addMousePressedListener();
	addMouseMovedListener();
	addKeyboardListener();
}

void Survive::Camera::addScrollListener()
{
	auto scrollListener = [this](double xOffset, double yOffset) {
		m_Position.z -= static_cast<float>(yOffset) * 2.0f;
	};
	Display::addScrollListener(scrollListener);
}

void Survive::Camera::addMousePressedListener()
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

void Survive::Camera::addMouseMovedListener()
{
	auto mouseMovedListener = [this](double mouseX, double mouseY) {
		float dy = static_cast<float>(mouseY) - m_MousePos.y;
		float dx = static_cast<float>(mouseX) - m_MousePos.x;

		if (m_LeftButtonPressed)
		{
			m_Rotation.y = m_CurrentRotation.y + dx / 2.0f;
			m_Rotation.x = m_CurrentRotation.x + dy / 2.0f;
		} else if (m_RightButtonPressed)
		{
			m_Pitch = m_CurrentPitch + dy / 5.0f;
			m_Yaw = m_CurrentYaw + dx / 5.0f;
		}
	};
	Display::addMouseMovedListener(mouseMovedListener);
}

void Survive::Camera::addKeyboardListener()
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

void Survive::Camera::invertPitch()
{
	m_Pitch = -m_Pitch;
}

void Survive::Camera::moveCameraInYDirection(float yDistance)
{
	m_Position.y += yDistance;
}
