//
// Created by david on 04. 11. 2021..
//

#include <imgui.h>

#include "EdgeGizmos.h"
#include "Maths.h"
#include "Constants.h"
#include "Util.h"

int Survive::EdgeGizmos::m_PointHovered = -1;

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

			ImVec2 p1 = getPoint(transform.position, edgeCollider.edgeShape.m_vertex1, camera, modelMatrix);
			ImVec2 p2 = getPoint(transform.position, edgeCollider.edgeShape.m_vertex2, camera, modelMatrix);

			m_Using = ImGui::IsMouseDragging(ImGuiMouseButton_Left);

			updateGizmo(camera, modelMatrix, transform.position, edgeCollider, p1, p2);
			drawGizmo(p1, p2);
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
	return m_PointHovered != -1;
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

ImVec2 Survive::EdgeGizmos::getPoint(const glm::vec3 &globalPos, const b2Vec2 &vertex, const Camera &camera,
									 const glm::mat4 &modelMatrix) const
{
	float scale = Constants::BOX2D_SCALE;

	glm::vec3 point = globalPos + glm::vec3{vertex.x / scale, vertex.y / scale, 0};
	return Util::getScreenPos(camera, modelMatrix, point, m_X, m_Y, m_Width, m_Height);
}

void Survive::EdgeGizmos::drawGizmo(const ImVec2 &p1, const ImVec2 &p2)
{
	static constexpr ImU32 POINT_COLOR = IM_COL32(0, 0, 255, 255);
	static constexpr ImU32 POINT_COLOR_HOVERED = IM_COL32(255, 90, 0, 255);
	static constexpr ImU32 LINE_COLOR = IM_COL32(255, 255, 255, 255);

	ImDrawList *drawList = ImGui::GetWindowDrawList();

	drawList->AddLine(p1, p2, LINE_COLOR, 3.0f);

	ImU32 color1 = m_PointHovered == 0 ? POINT_COLOR_HOVERED : POINT_COLOR;
	ImU32 color2 = m_PointHovered == 1 ? POINT_COLOR_HOVERED : POINT_COLOR;
	drawList->AddCircleFilled(p1, RADIUS, color1);
	drawList->AddCircleFilled(p2, RADIUS, color2);
}

void Survive::EdgeGizmos::moveVertex(const Camera &camera, const glm::mat4 &modelMatrix, const glm::vec3 &position,
									 b2Vec2 &vertex) const
{
	ImVec2 mousePosition = ImGui::GetMousePos();

	glm::vec3 localPos = Util::getLocalSpace(camera, modelMatrix, mousePosition, m_X, m_Y, m_Width,
											 m_Height);

	localPos *= Constants::BOX2D_SCALE;
	glm::vec3 offset = position * Constants::BOX2D_SCALE;

	glm::vec3 newPosition = localPos - offset;
	vertex = b2Vec2(newPosition.x, newPosition.y);
}

void
Survive::EdgeGizmos::updateGizmo(const Camera &camera, const glm::mat4 &modelMatrix, const glm::vec3 &position,
								 EdgeCollider2DComponent &edgeCollider, const ImVec2 &p1, const ImVec2 &p2)
{
	if (!m_Using && Util::mouseHoversPoint(p1, RADIUS))
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
		m_PointHovered = 0;
	} else if (!m_Using && Util::mouseHoversPoint(p2, RADIUS))
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
		m_PointHovered = 1;
	} else if (!m_Using)
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
		m_PointHovered = -1;
	}

	if (m_Using && m_PointHovered == 0)
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
		moveVertex(camera, modelMatrix, position, edgeCollider.edgeShape.m_vertex1);
	} else if (m_Using && m_PointHovered == 1)
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
		moveVertex(camera, modelMatrix, position, edgeCollider.edgeShape.m_vertex2);
	}
}
