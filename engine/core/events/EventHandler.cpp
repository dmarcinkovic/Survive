//
// Created by david on 08. 01. 2021..
//

#include <imgui.h>
#include <vector>

#include "EventHandler.h"

std::vector<Survive::KeyListener> Survive::EventHandler::m_KeyEventListeners;
std::vector<Survive::MouseListener> Survive::EventHandler::m_MouseEventListeners;
std::vector<Survive::MouseMovedListener> Survive::EventHandler::m_MouseMoveListeners;
std::vector<Survive::WindowListener> Survive::EventHandler::m_WindowListeners;
std::vector<Survive::ScrollListener> Survive::EventHandler::m_ScrollListeners;

Survive::EventHandler::EventHandler()
{
	addKeyboardListener();
}

void Survive::EventHandler::addKeyboardListener()
{
	addKeyListener([this](int key, int action) {
		if (action == GLFW_PRESS)
		{
			m_Keys[key] = true;
		} else if (action == GLFW_RELEASE)
		{
			m_Keys[key] = false;
		}
	});
}

bool Survive::EventHandler::isKeyControlPressed() const
{
	return m_Keys[Key::RIGHT_CONTROL] || m_Keys[Key::LEFT_CONTROL];
}

bool Survive::EventHandler::isKeyPressed(Key key) const
{
	return m_Keys[key];
}

bool Survive::EventHandler::isShiftKeyPressed() const
{
	return m_Keys[Key::RIGHT_SHIFT] || m_Keys[Key::LEFT_SHIFT];
}

void Survive::EventHandler::addKeyListener(const Survive::KeyListener &listener)
{
	m_KeyEventListeners.emplace_back(listener);
}

void Survive::EventHandler::addMouseListener(const Survive::MouseListener &listener)
{
	m_MouseEventListeners.emplace_back(listener);
}

void Survive::EventHandler::addScrollListener(const Survive::ScrollListener &listener)
{
	m_ScrollListeners.emplace_back(listener);
}

void Survive::EventHandler::addMouseMovedListener(const Survive::MouseMovedListener &listener)
{
	m_MouseMoveListeners.emplace_back(listener);
}

void Survive::EventHandler::addWindowResizeListener(const Survive::WindowListener &listener)
{
	m_WindowListeners.emplace_back(listener);
}

void Survive::EventHandler::windowResizeCallback(GLFWwindow *, int width, int height)
{
	for (auto const &listener : m_WindowListeners)
	{
		listener(width, height);
	}
}

void Survive::EventHandler::keyEventCallback(GLFWwindow *, int key, int, int action, int)
{
	for (auto const &listener : m_KeyEventListeners)
	{
		listener(key, action);
	}
}

void Survive::EventHandler::mouseEventCallback(GLFWwindow *window, int button, int action, int)
{
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	for (auto const &listener : m_MouseEventListeners)
	{
		listener(button, action, mouseX, mouseY);
	}
}

void Survive::EventHandler::mousePositionCallback(GLFWwindow *, double mouseX, double mouseY)
{
	for (auto const &listener : m_MouseMoveListeners)
	{
		listener(mouseX, mouseY);
	}
}

void Survive::EventHandler::scrollCallback(GLFWwindow *, double xOffset, double yOffset)
{
	for (auto const &listener : m_ScrollListeners)
	{
		listener(xOffset, yOffset);
	}
}
