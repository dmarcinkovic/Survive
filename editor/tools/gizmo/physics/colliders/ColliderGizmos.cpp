//
// Created by david on 06. 11. 2021..
//

#include "ColliderGizmos.h"

void Survive::ColliderGizmos::draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity)
{

}

void Survive::ColliderGizmos::handleKeyEvents(const EventHandler &eventHandler)
{
	if (eventHandler.isKeyPressed(Key::A))
	{
		m_GizmoEnabled = true;
	} else if (eventHandler.isKeyPressed(Key::ESCAPE))
	{
		m_GizmoEnabled = false;
	}
}

void Survive::ColliderGizmos::setRect(float x, float y, float width, float height)
{
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;
}

bool Survive::ColliderGizmos::isEnabled() const
{
	return m_GizmoEnabled;
}
