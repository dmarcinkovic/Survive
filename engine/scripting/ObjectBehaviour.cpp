//
// Created by david on 24. 02. 2022..
//

#include <imgui.h>

#include "ObjectBehaviour.h"

void Survive::ObjectBehaviour::init(entt::registry &registry, entt::entity entity, EventHandler &eventHandler)
{
	m_Registry = &registry;
	m_Entity = entity;
	m_EventHandler = &eventHandler;
}

bool Survive::ObjectBehaviour::isKeyPressed(Key key) const
{
	if (m_EventHandler != nullptr)
	{
		return m_EventHandler->isKeyPressed(key);
	}

	return false;
}

std::pair<float, float> Survive::ObjectBehaviour::getMousePosition()
{
	ImVec2 mousePosition = ImGui::GetMousePos();
	return std::make_pair(mousePosition.x, mousePosition.y);
}

float Survive::ObjectBehaviour::getDeltaTime()
{
	return static_cast<float>(Display::getFrameTime());
}

void Survive::ObjectBehaviour::start()
{

}

void Survive::ObjectBehaviour::update()
{

}

void Survive::ObjectBehaviour::onMouseClick()
{

}

void Survive::ObjectBehaviour::onCollision()
{

}

void Survive::ObjectBehaviour::onDestroy()
{

}

void Survive::ObjectBehaviour::onKeyboardPressed()
{

}
