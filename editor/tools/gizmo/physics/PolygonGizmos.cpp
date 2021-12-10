//
// Created by david on 28. 11. 2021..
//

#include "PolygonGizmos.h"
#include "Maths.h"
#include "Util.h"
#include "Constants.h"

int Survive::PolygonGizmos::m_PointHovered = -1;

void Survive::PolygonGizmos::draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity)
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

		if (m_GizmoEnabled)
		{
			glm::mat4 modelMatrix = Maths::createTransformationMatrix(transform.position);

			m_IsUsing = ImGui::IsMouseDragging(ImGuiMouseButton_Left);

			float angle = glm::radians(transform.rotation.z);
			const glm::vec3 &position = transform.position;
			std::vector<b2Vec2> &points = polygonCollider.points;
			std::vector<ImVec2> polygonPoints = getPolygonPoints(points, position, camera, modelMatrix, angle);

			updateGizmo(camera, modelMatrix, position, polygonPoints, points, polygonCollider.polygonShape);
			drawGizmos(polygonPoints);
		}
	}
}

bool Survive::PolygonGizmos::isOver()
{
	return m_PointHovered != -1;
}

ImVec2 Survive::PolygonGizmos::getPoint(const glm::vec3 &globalPos, const b2Vec2 &vertex, const Camera &camera,
										const glm::mat4 &modelMatrix, float angle) const
{
	float scale = Constants::BOX2D_SCALE;

	float x = vertex.x / scale;
	float y = vertex.y / scale;

	float cosAngle = std::cos(angle);
	float sinAngle = std::sin(angle);
	glm::vec3 rotatedPoint{x * cosAngle - y * sinAngle, y * cosAngle + x * sinAngle, 0};
	glm::vec3 point = globalPos + rotatedPoint;

	return Util::getScreenPos(camera, modelMatrix, point, m_X, m_Y, m_Width, m_Height);
}

std::vector<ImVec2>
Survive::PolygonGizmos::getPolygonPoints(const std::vector<b2Vec2> &points, const glm::vec3 &globalPos,
										 const Camera &camera, const glm::mat4 &modelMatrix, float angle)
{
	std::vector<ImVec2> polygonPoints;
	polygonPoints.reserve(points.size());

	for (const b2Vec2 &point: points)
	{
		polygonPoints.emplace_back(getPoint(globalPos, point, camera, modelMatrix, angle));
	}

	return polygonPoints;
}

void Survive::PolygonGizmos::drawPoints(const std::vector<ImVec2> &points)
{
	static constexpr ImU32 POINT_COLOR = IM_COL32(0, 0, 255, 255);
	static constexpr ImU32 POINT_COLOR_HOVERED = IM_COL32(255, 90, 0, 255);
	static constexpr float RADIUS = 5.0f;

	ImDrawList *drawList = ImGui::GetWindowDrawList();

	for (int i = 0; i < points.size(); ++i)
	{
		ImU32 color = m_PointHovered == i ? POINT_COLOR_HOVERED : POINT_COLOR;
		drawList->AddCircleFilled(points[i], RADIUS, color);
	}
}

void Survive::PolygonGizmos::drawLines(const std::vector<ImVec2> &points)
{
	static constexpr ImU32 LINE_COLOR = IM_COL32(255, 255, 255, 255);

	if (points.size() < 3)
	{
		return;
	}

	ImDrawList *drawList = ImGui::GetWindowDrawList();
	for (int i = 0; i < points.size(); ++i)
	{
		const ImVec2 &p1 = points[i];
		const ImVec2 &p2 = points[(i + 1) % points.size()];

		drawList->AddLine(p1, p2, LINE_COLOR, 3.0f);
	}
}

void Survive::PolygonGizmos::drawGizmos(const std::vector<ImVec2> &polygonPoints)
{
	drawLines(polygonPoints);
	drawPoints(polygonPoints);
}

void Survive::PolygonGizmos::updateGizmo(const Camera &camera, const glm::mat4 &modelMatrix,
										 const glm::vec3 &position, const std::vector<ImVec2> &polygonPoints,
										 std::vector<b2Vec2> &points, b2PolygonShape &shape)
{
	static constexpr float RADIUS = 5.0f;

	bool hovered{};
	for (int i = 0; i < polygonPoints.size(); ++i)
	{
		if (!m_IsUsing && Util::mouseHoversPoint(polygonPoints[i], RADIUS))
		{
			ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
			m_PointHovered = i;
			hovered = true;

			break;
		}
	}

	if (!hovered && !m_IsUsing)
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
		m_PointHovered = -1;
	}

	for (int i = 0; i < points.size(); ++i)
	{
		if (m_IsUsing && m_PointHovered == i)
		{
			ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
			moveVertex(camera, modelMatrix, position, points[i]);
			shape.Set(points.data(), static_cast<int>(points.size()));
		}
	}
}

void Survive::PolygonGizmos::moveVertex(const Camera &camera, const glm::mat4 &modelMatrix, const glm::vec3 &position,
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
