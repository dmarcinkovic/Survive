//
// Created by david on 08. 01. 2021..
//

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
			m_Key = key;
		} else if (action == GLFW_RELEASE)
		{
			m_Key = -1;
		}
	};

	Display::addKeyListener(keyboardListener);
}

int Survive::EventHandler::getKeyPressed() const
{
	return m_Key;
}

bool Survive::EventHandler::isKeyControlPressed()
{
	return GLFW_MOD_CONTROL;
}
