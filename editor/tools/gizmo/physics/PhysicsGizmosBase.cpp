//
// Created by david on 06. 11. 2021..
//

#include "PhysicsGizmosBase.h"

void Survive::PhysicsGizmosBase::draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity)
{

}

void Survive::PhysicsGizmosBase::handleKeyEvents(const EventHandler &eventHandler)
{
	if (eventHandler.isKeyPressed(Key::A))
	{
		m_GizmoEnabled = true;
	} else if (eventHandler.isKeyPressed(Key::ESCAPE))
	{
		m_GizmoEnabled = false;
	}
}

void Survive::PhysicsGizmosBase::setRect(float x, float y, float width, float height)
{
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;
}

bool Survive::PhysicsGizmosBase::isEnabled() const
{
	return m_GizmoEnabled;
}
