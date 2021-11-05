//
// Created by david on 01. 11. 2021..
//

#include <imgui.h>

#include "Components.h"
#include "CircleGizmos.h"
#include "Constants.h"
#include "Util.h"
#include "Maths.h"

bool Survive::CircleGizmos::m_Hovered{};
bool Survive::CircleGizmos::m_CenterHovered{};

void Survive::CircleGizmos::draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity)
{
	if (selectedEntity != entt::null &&
		registry.all_of<Render2DComponent, CircleCollider2DComponent, Transform3DComponent>(selectedEntity))
	{
		CircleCollider2DComponent &circleCollider = registry.get<CircleCollider2DComponent>(selectedEntity);
		const Transform3DComponent &transform = registry.get<Transform3DComponent>(selectedEntity);

		initializeCircleCollider(circleCollider, transform);

		if (m_GizmoEnabled)
		{
			drawGizmos(transform, circleCollider, camera);
		}
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
	return m_Hovered || m_CenterHovered;
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

void Survive::CircleGizmos::initializeCircleCollider(CircleCollider2DComponent &circleCollider,
													 const Transform3DComponent &transform)
{
	if (!circleCollider.m_Initialized)
	{
		const glm::vec3 &scale = transform.scale;

		circleCollider.circleShape.m_radius = std::min(scale.x, scale.y) * Constants::BOX2D_SCALE;
		circleCollider.m_Initialized = true;
	}
}

void Survive::CircleGizmos::drawCircle(const ImVec2 &center, float radius)
{
	static constexpr ImU32 CIRCLE_COLOR = IM_COL32(255, 255, 255, 255);
	static constexpr ImU32 CIRCLE_COLOR_HOVERED = IM_COL32(255, 90, 0, 255);
	static constexpr float THICKNESS = 3.0f;

	ImDrawList *drawList = ImGui::GetWindowDrawList();

	ImU32 color = m_Hovered ? CIRCLE_COLOR_HOVERED : CIRCLE_COLOR;
	drawList->AddCircle(center, radius, color, 0, THICKNESS);
}

void Survive::CircleGizmos::updateCircleRadius(const ImVec2 &center, float radius, const Camera &camera,
											   const glm::mat4 &modelMatrix,
											   CircleCollider2DComponent &circleCollider) const
{
	if (!m_Using && mouseHoversCircle(center, radius) && !m_CenterHovered)
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
		m_Hovered = true;
	} else if (!m_Using)
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
		m_Hovered = false;
	}

	if (m_Using && m_Hovered)
	{
		ImVec2 mousePosition = ImGui::GetMousePos();
		float newRadius = Util::lineDistance(mousePosition, center) + m_X + m_Width / 2.0f;

		glm::vec3 localPos = Util::getLocalSpace(camera, modelMatrix, ImVec2(newRadius, 0), m_X, m_Y, m_Width,
												 m_Height);
		circleCollider.circleShape.m_radius = localPos.x * Constants::BOX2D_SCALE;

		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}
}

void Survive::CircleGizmos::drawCenter(const ImVec2 &center)
{
	static constexpr ImU32 COLOR = IM_COL32(255, 255, 255, 255);
	static constexpr ImU32 COLOR_HOVERED = IM_COL32(255, 90, 0, 255);

	ImDrawList *drawList = ImGui::GetWindowDrawList();

	ImU32 color = m_CenterHovered ? COLOR_HOVERED : COLOR;
	drawList->AddCircle(center, 4.0, color, 0, 2.0f);
}

void Survive::CircleGizmos::updateCircleCenter(const ImVec2 &center, const Camera &camera, const glm::mat4 &modelMatrix,
											   CircleCollider2DComponent &circleCollider,
											   const Transform3DComponent &transform) const
{
	if (!m_Using && !m_Hovered && Util::mouseHoversPoint(center, RADIUS))
	{
		m_CenterHovered = true;
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	} else if (!m_Using)
	{
		m_CenterHovered = false;
	}

	if (m_Using && m_CenterHovered)
	{
		ImVec2 mousePosition = ImGui::GetMousePos();

		glm::vec3 localPos = Util::getLocalSpace(camera, modelMatrix, mousePosition, m_X, m_Y, m_Width, m_Height);

		glm::vec3 offset = transform.position * Constants::BOX2D_SCALE;
		localPos *= Constants::BOX2D_SCALE;

		glm::vec3 circleCenter = localPos - offset;
		circleCollider.circleShape.m_p = b2Vec2(circleCenter.x, circleCenter.y);

		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}
}

void Survive::CircleGizmos::drawGizmos(const Transform3DComponent &transform,
									   Survive::CircleCollider2DComponent &circleCollider,
									   const Camera &camera)
{
	glm::mat4 modelMatrix = Maths::createTransformationMatrix(transform.position);

	ImVec2 center = getCircleCenter(circleCollider, camera, transform, modelMatrix);
	float radius = calculateRadius(circleCollider.circleShape.m_radius, camera, modelMatrix);

	m_Using = ImGui::IsMouseDragging(ImGuiMouseButton_Left);

	updateCircleRadius(center, radius, camera, modelMatrix, circleCollider);
	updateCircleCenter(center, camera, modelMatrix, circleCollider, transform);

	drawCircle(center, radius);
	drawCenter(center);
}
