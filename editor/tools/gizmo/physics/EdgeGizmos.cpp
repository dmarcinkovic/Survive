//
// Created by david on 04. 11. 2021..
//

#include "EdgeGizmos.h"
#include "Maths.h"
#include "Constants.h"

void Survive::EdgeGizmos::draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity)
{
	if (selectedEntity != entt::null &&
		registry.all_of<EdgeCollider2DComponent, Transform3DComponent, Render2DComponent>(selectedEntity))
	{
		EdgeCollider2DComponent &edgeCollider = registry.get<EdgeCollider2DComponent>(selectedEntity);
		const Transform3DComponent &transform = registry.get<Transform3DComponent>(selectedEntity);

		initializeEdgeCollider(edgeCollider, transform);

		if (m_GizmoEnabled)
		{
			glm::mat4 modelMatrix = Maths::createTransformationMatrix(transform.position);


		}
	}
}

void Survive::EdgeGizmos::handleKeyEvents(const EventHandler &eventHandler)
{
	if (eventHandler.isKeyPressed(Key::A))
	{
		m_GizmoEnabled = true;
	} else if (eventHandler.isKeyPressed(Key::ESCAPE))
	{
		m_GizmoEnabled = false;
	}
}

void Survive::EdgeGizmos::setRect(float x, float y, float width, float height)
{
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;
}

bool Survive::EdgeGizmos::isOver()
{
	return false;
}

void Survive::EdgeGizmos::initializeEdgeCollider(EdgeCollider2DComponent &edgeCollider,
												 const Transform3DComponent &transform)
{
	if (!edgeCollider.m_Initialized)
	{
		glm::vec3 scale = transform.scale * Constants::BOX2D_SCALE;

		edgeCollider.edgeShape.m_vertex1 = b2Vec2(-scale.x, scale.y);
		edgeCollider.edgeShape.m_vertex2 = b2Vec2(scale.x, scale.y);

		edgeCollider.m_Initialized = true;
	}
}
