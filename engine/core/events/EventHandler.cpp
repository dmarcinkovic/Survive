//
// Created by david on 08. 01. 2021..
//

#include <imgui.h>

#include "EventHandler.h"
#include "Display.h"

Survive::EventHandler::EventHandler()
{
	addKeyboardListener();
}

void Survive::EventHandler::addKeyboardListener()
{
	auto keyboardListener = [this](int key, int action) {
		if (action == GLFW_PRESS)
		{
			m_Keys[key] = true;
		} else if (action == GLFW_RELEASE)
		{
			m_Keys[key] = false;
		}
	};

	Display::addKeyListener(keyboardListener);
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
