//
// Created by david on 28. 11. 2021..
//

#include "PolygonGizmos.h"
#include "Maths.h"

void Survive::PolygonGizmos::draw(entt::registry &registry, const Survive::Camera &camera, entt::entity selectedEntity)
{
	if (selectedEntity == entt::null)
	{
		m_GizmoEnabled = false;
	}

	if (selectedEntity != entt::null &&
		registry.all_of<PolygonCollider2DComponent, Transform3DComponent>(selectedEntity))
	{
		PolygonCollider2DComponent &polygonCollider = registry.get<PolygonCollider2DComponent>(selectedEntity);
		const Transform3DComponent &transform = registry.get<Transform3DComponent>(selectedEntity);

		initializePolygonCollider(polygonCollider, transform);

		if (m_GizmoEnabled)
		{
			glm::mat4 modelMatrix = Maths::createTransformationMatrix(transform.position);

		}
	}
}

bool Survive::PolygonGizmos::isOver()
{
	return false;
}

void Survive::PolygonGizmos::initializePolygonCollider(Survive::PolygonCollider2DComponent &polygonCollider,
													   const Survive::Transform3DComponent &transform)
{

}
