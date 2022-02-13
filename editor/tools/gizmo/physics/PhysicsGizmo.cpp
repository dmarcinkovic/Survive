//
// Created by david on 24. 10. 2021..
//


#include "PhysicsGizmo.h"

void Survive::PhysicsGizmo::draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity)
{
	m_BoxGizmos.draw(registry, camera, selectedEntity);
	m_CircleGizmos.draw(registry, camera, selectedEntity);
	m_EdgeGizmos.draw(registry, camera, selectedEntity);
	m_PolygonGizmos.draw(registry, camera, selectedEntity);

	m_HingeGizmos.draw(registry, camera, selectedEntity);
}

void Survive::PhysicsGizmo::handleKeyEvents(const EventHandler &eventHandler)
{
	if (!isColliderGizmosEnabled())
	{
		m_HingeGizmos.handleKeyEvents(eventHandler);
	}

	if (!m_HingeGizmos.isEnabled())
	{
		m_BoxGizmos.handleKeyEvents(eventHandler);
		m_CircleGizmos.handleKeyEvents(eventHandler);
		m_EdgeGizmos.handleKeyEvents(eventHandler);
		m_PolygonGizmos.handleKeyEvents(eventHandler);
	}
}

void Survive::PhysicsGizmo::setRect(float x, float y, float width, float height)
{
	m_BoxGizmos.setRect(x, y, width, height);
	m_CircleGizmos.setRect(x, y, width, height);
	m_EdgeGizmos.setRect(x, y, width, height);
	m_PolygonGizmos.setRect(x, y, width, height);

	m_HingeGizmos.setRect(x, y, width, height);
}

bool Survive::PhysicsGizmo::isOver()
{
	return BoxGizmos::isOver() || CircleGizmos::isOver() || EdgeGizmos::isOver() || PolygonGizmos::isOver() ||
		   HingeJointGizmos::isOver();
}

bool Survive::PhysicsGizmo::isEnabled() const
{
	return isColliderGizmosEnabled() || m_HingeGizmos.isEnabled();
}

bool Survive::PhysicsGizmo::isColliderGizmosEnabled() const
{
	return m_BoxGizmos.isEnabled() || m_CircleGizmos.isEnabled() || m_EdgeGizmos.isEnabled() ||
		   m_PolygonGizmos.isEnabled();
}
