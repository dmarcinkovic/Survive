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
		float radius = calculateRadius(circleCollider.circleShape.m_radius, camera, modelMatrix);

		ImU32 color = mouseHoversCircle(center, radius) ? CIRCLE_COLOR_HOVERED : CIRCLE_COLOR;
		drawList->AddCircle(center, radius, color, 0, THICKNESS);
	}
}

void Survive::CircleGizmos::handleKeyEvents(const EventHandler &eventHandler)
{
	if (eventHandler.isKeyPressed(Key::A))
	{
		m_GizmoEnabled = true;
	} else if (eventHandler.isKeyPressed(Key::ESCAPE))
	{
		m_GizmoEnabled = false;
	}
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
											  const glm::mat4 &modelMatrix) const
{
	b2Vec2 circleCenter = circleCollider.circleShape.m_p;

	return Util::getCenter(circleCenter, camera, transform, modelMatrix, m_X, m_Y, m_Width, m_Height);
}

float Survive::CircleGizmos::calculateRadius(float radius, const Camera &camera, const glm::mat4 &modelMatrix) const
{
	float circleRadius = radius / Constants::BOX2D_SCALE;
	ImVec2 r = Util::getScreenPos(camera, modelMatrix, glm::vec2{circleRadius}, m_X, m_Y, m_Width, m_Height);

	return r.x - m_Width / 2.0f - m_X;
}

bool Survive::CircleGizmos::mouseHoversCircle(const ImVec2 &center, float radius)
{
	static constexpr float THRESHOLD = 4.0f;

	ImVec2 mousePosition = ImGui::GetMousePos();
	float centerMouseDistance = Util::lineDistance(mousePosition, center);

	return std::abs(radius - centerMouseDistance) < THRESHOLD;
}
