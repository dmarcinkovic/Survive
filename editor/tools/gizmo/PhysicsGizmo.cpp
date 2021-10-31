//
// Created by david on 24. 10. 2021..
//


#include "PhysicsGizmo.h"

void Survive::PhysicsGizmo::draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity)
{
	m_BoxGizmos.draw(registry, camera, selectedEntity);
}

void Survive::PhysicsGizmo::handleKeyEvents(const EventHandler &eventHandler)
{
	m_BoxGizmos.handleKeyEvents(eventHandler);
}

void Survive::PhysicsGizmo::setRect(float x, float y, float width, float height)
{
	m_BoxGizmos.setRect(x, y, width, height);
}

bool Survive::PhysicsGizmo::isOver()
{
	return BoxGizmos::isOver();
}
