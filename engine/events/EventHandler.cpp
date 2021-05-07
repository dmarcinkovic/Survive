//
// Created by david on 08. 01. 2021..
//

#include "EventHandler.h"
#include "../display/Display.h"

Survive::EventHandler::EventHandler(Camera &camera)
	: m_Camera(camera)
{
}

void Survive::EventHandler::registerListener(bool &active)
{
	m_Active = &active;

	addScrollListener();

	addMousePressedListener();

	addMouseMovedListener();

	addKeyboardListener();
}

void Survive::EventHandler::addScrollListener()
{
	auto scrollListener = [this](double xOffset, double yOffset) {
		if (*m_Active)
		{
			m_Camera.position.z -= yOffset * 2.0f;
		}
	};

	Display::addScrollListener(scrollListener);
}

void Survive::EventHandler::addMousePressedListener()
{
	auto mousePressedListener = [this](int button, int action, double mouseX, double mouseY) {
		if (action == GLFW_PRESS && *m_Active)
		{
			if (button == GLFW_MOUSE_BUTTON_RIGHT)
			{
				m_RightButtonPressed = true;
			} else
			{
				m_LeftButtonPressed = true;
			}

			m_MousePos = glm::vec2{mouseX, mouseY};
			m_CurrentRotation = m_Camera.rotation;
			m_CurrentPitch = m_Camera.pitch;
			m_CurrentYaw = m_Camera.yaw;
		} else
		{
			m_LeftButtonPressed = false;
			m_RightButtonPressed = false;
		}
	};

	Display::addMouseListener(mousePressedListener);
}

void Survive::EventHandler::addMouseMovedListener()
{
	auto mouseMovedListener = [this](double mouseX, double mouseY) {
		if (!*m_Active)
		{
			return;
		}

		double dx = mouseX - m_MousePos.x;
		double dy = mouseY - m_MousePos.y;

		if (m_LeftButtonPressed)
		{
			m_Camera.rotation.y = m_CurrentRotation.y + dx / 2.0f;
			m_Camera.rotation.x = m_CurrentRotation.x + dy / 2.0f;
		} else if (m_RightButtonPressed)
		{
			m_Camera.pitch = m_CurrentPitch + static_cast<float >(dy / 5.0);
			m_Camera.yaw = m_CurrentYaw + static_cast<float >(dx / 5.0);
		}
	};

	Display::addMouseMovedListener(mouseMovedListener);
}

void Survive::EventHandler::addKeyboardListener()
{
	auto keyboardListener = [this](int key, int action) {
		if (action == GLFW_PRESS && *m_Active)
		{
			switch (key)
			{
				case GLFW_KEY_LEFT :
					m_Camera.position.x -= 0.3;
					break;
				case GLFW_KEY_RIGHT :
					m_Camera.position.x += 0.3;
					break;
				case GLFW_KEY_DOWN :
					m_Camera.position.y -= 0.3;
					break;
				case GLFW_KEY_UP :
					m_Camera.position.y += 0.3;
					break;
				default:
					break;
			}
		}
	};

	Display::addKeyListener(keyboardListener);
}
