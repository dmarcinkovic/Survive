//
// Created by david on 06. 11. 2021..
//

#include "PhysicsGizmosBase.h"
#include "Util.h"
#include "Constants.h"

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

ImVec2
Survive::PhysicsGizmosBase::getPoint(const glm::vec3 &globalPos, const b2Vec2 &vertex, const Camera &camera,
									 const glm::mat4 &modelMatrix, float angle) const
{
	float scale = Constants::BOX2D_SCALE;

	glm::vec3 rotatedPoint = rotatePointAroundOrigin(vertex.x / scale, vertex.y / scale, angle);
	glm::vec3 point = globalPos + rotatedPoint;

	return Util::getScreenPos(camera, modelMatrix, point, m_X, m_Y, m_Width, m_Height);
}

glm::vec3 Survive::PhysicsGizmosBase::rotatePointAroundOrigin(float x, float y, float angle)
{
	float cosAngle = std::cos(angle);
	float sinAngle = std::sin(angle);

	return {x * cosAngle - y * sinAngle, y * cosAngle + x * sinAngle, 0};
}
