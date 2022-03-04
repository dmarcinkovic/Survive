//
// Created by david on 24. 02. 2022..
//

#include <imgui.h>

#include "ObjectBehaviour.h"
#include "TagComponent.h"
#include "RegistryUtil.h"

void Survive::ObjectBehaviour::init(entt::registry &registry, entt::entity entity, EventHandler &eventHandler)
{
	m_Registry = &registry;
	m_Entity = entity;
	m_EventHandler = &eventHandler;

	m_NeedRestore = false;
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

std::string Survive::ObjectBehaviour::getTag(entt::entity entity) const
{
	if (m_Registry->any_of<TagComponent>(entity))
	{
		const TagComponent &tag = m_Registry->get<TagComponent>(entity);

		return tag.tag;
	}

	return "";
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

void Survive::ObjectBehaviour::onDestroy()
{

}

void Survive::ObjectBehaviour::onKeyboardPressed()
{

}

void Survive::ObjectBehaviour::onCollisionEnter(entt::entity other)
{

}

void Survive::ObjectBehaviour::onCollisionExit(entt::entity other)
{

}

void Survive::ObjectBehaviour::storeEntity()
{
	if (!m_Registry->any_of<TagComponent>(m_Entity))
	{
		return;
	}

	entt::entity destination = m_Registry->create();
	RegistryUtil::copyEntity(*m_Registry, m_Entity, destination);

	m_Registry->remove<TagComponent>(destination);
	m_CopiedEntities[m_Entity] = destination;

	m_NeedRestore = true;
}

void Survive::ObjectBehaviour::restoreEntity()
{
	if (m_Registry->valid(m_Entity))
	{
		m_Registry->destroy(m_Entity);
	}

	const TagComponent &tag = m_Registry->get<TagComponent>(m_Entity);
	entt::entity copy = m_CopiedEntities[m_Entity];

	m_Registry->emplace<TagComponent>(copy, tag.tag);
	m_CopiedEntities.erase(m_Entity);
}
