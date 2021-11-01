//
// Created by david on 01. 11. 2021..
//

#include <imgui.h>

#include "Components.h"
#include "CircleGizmos.h"
#include "Constants.h"
#include "Util.h"
#include "Maths.h"

void Survive::CircleGizmos::draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity)
{
	if (m_GizmoEnabled && selectedEntity != entt::null &&
		registry.all_of<Render2DComponent, CircleCollider2DComponent, Transform3DComponent>(selectedEntity))
	{
		CircleCollider2DComponent &circleCollider = registry.get<CircleCollider2DComponent>(selectedEntity);
		const Transform3DComponent &transform = registry.get<Transform3DComponent>(selectedEntity);

		glm::mat4 modelMatrix = Maths::createTransformationMatrix(transform.position);

		ImDrawList *drawList = ImGui::GetWindowDrawList();

		ImVec2 center = getCircleCenter(circleCollider, camera, transform, modelMatrix);

		drawList->AddCircle(center, 100, IM_COL32(255, 0, 0, 255), 0, 3.0f);
	}
}

void Survive::CircleGizmos::handleKeyEvents(const Survive::EventHandler &eventHandler)
{

}

void Survive::CircleGizmos::setRect(float x, float y, float width, float height)
{
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;
}

bool Survive::CircleGizmos::isOver()
{
	return false;
}

ImVec2 Survive::CircleGizmos::getCircleCenter(const CircleCollider2DComponent &circleCollider,
											  const Camera &camera, const Transform3DComponent &transform,
											  const glm::mat4 &modelMatrix)
{
	b2Vec2 circleCenter = circleCollider.circleShape.m_p;

	return Util::getCenter(circleCenter, camera, transform, modelMatrix, m_X, m_Y, m_Width, m_Height);
}