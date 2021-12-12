//
// Created by david on 31. 10. 2021..
//

#include <imgui.h>

#include "Maths.h"
#include "Constants.h"
#include "BoxGizmos.h"
#include "Util.h"
#include "EditorUtil.h"

int Survive::BoxGizmos::m_HoveredLine = -1;
bool Survive::BoxGizmos::m_CenterHovered{};

void Survive::BoxGizmos::draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity)
{
	if (selectedEntity == entt::null)
	{
		m_GizmoEnabled = false;
	}

	if (selectedEntity != entt::null &&
		registry.all_of<BoxCollider2DComponent, Transform3DComponent>(selectedEntity))
	{
		BoxCollider2DComponent &boxCollider = registry.get<BoxCollider2DComponent>(selectedEntity);
		const Transform3DComponent &transform = registry.get<Transform3DComponent>(selectedEntity);

		initializeBoxCollider(boxCollider, transform);

		if (m_GizmoEnabled)
		{
			glm::mat4 transformationMatrix = Maths::createTransformationMatrix(transform.position);

			m_IsUsing = ImGui::IsMouseDragging(ImGuiMouseButton_Left);
			drawBoxColliderGizmo(camera, boxCollider, transform, transformationMatrix);
		}
	}
}

void Survive::BoxGizmos::drawBoxColliderGizmo(const Camera &camera, BoxCollider2DComponent &boxCollider,
											  const Transform3DComponent &transform, const glm::mat4 &modelMatrix)
{
	float angle = glm::radians(transform.rotation.z);

	ImVec2 center = calcCenter(boxCollider.center, camera, transform.position, modelMatrix, angle);

	b2Vec2 *vertices = boxCollider.boxShape.m_vertices;
	std::vector<b2Vec2> points{vertices, vertices + 4};

	std::vector<ImVec2> rectanglePoints = getPolygonPoints(points, transform.position, camera, modelMatrix, angle);

	updateGizmos(camera, boxCollider, transform, modelMatrix, rectanglePoints, center);

	drawRect(rectanglePoints, m_HoveredLine);
	drawCenter(center, m_CenterHovered);
}

void Survive::BoxGizmos::initializeBoxCollider(BoxCollider2DComponent &boxCollider,
											   const Transform3DComponent &transform)
{
	if (!boxCollider.m_Initialized)
	{
		boxCollider.width = transform.scale.x * Constants::BOX2D_SCALE;
		boxCollider.height = transform.scale.y * Constants::BOX2D_SCALE;
		boxCollider.boxShape.SetAsBox(boxCollider.width, boxCollider.height);

		boxCollider.m_Initialized = true;
	}
}

void Survive::BoxGizmos::drawRect(const std::vector<ImVec2> &points, int hoveredLine)
{
	static constexpr float CIRCLE_RADIUS = 5.0f;
	static constexpr ImU32 CIRCLE_COLOR = IM_COL32(0, 0, 255, 255);

	ImDrawList *drawList = ImGui::GetWindowDrawList();

	drawLine(drawList, points[0], points[1], hoveredLine == 0);
	drawLine(drawList, points[1], points[2], hoveredLine == 1);
	drawLine(drawList, points[2], points[3], hoveredLine == 2);
	drawLine(drawList, points[3], points[0], hoveredLine == 3);

	drawList->AddCircleFilled(points[0], CIRCLE_RADIUS, CIRCLE_COLOR);
	drawList->AddCircleFilled(points[1], CIRCLE_RADIUS, CIRCLE_COLOR);
	drawList->AddCircleFilled(points[2], CIRCLE_RADIUS, CIRCLE_COLOR);
	drawList->AddCircleFilled(points[3], CIRCLE_RADIUS, CIRCLE_COLOR);
}

void Survive::BoxGizmos::drawLine(ImDrawList *drawList, const ImVec2 &p1, const ImVec2 &p2, bool isHovered)
{
	static constexpr float LINE_THICKNESS = 2.0f;
	static constexpr ImU32 LINE_COLOR = IM_COL32(255, 255, 255, 255);
	static constexpr ImU32 LINE_COLOR_HOVERED = IM_COL32(255, 90, 0, 255);

	ImU32 color = isHovered ? LINE_COLOR_HOVERED : LINE_COLOR;
	drawList->AddLine(p1, p2, color, LINE_THICKNESS);
}

void Survive::BoxGizmos::drawCenter(const ImVec2 &boxCenter, bool isHovered)
{
	static constexpr ImU32 POINT_COLOR = IM_COL32(255, 255, 255, 255);
	static constexpr ImU32 POINT_COLOR_HOVERED = IM_COL32(255, 90, 0, 255);

	ImDrawList *drawList = ImGui::GetWindowDrawList();

	ImU32 color = isHovered ? POINT_COLOR_HOVERED : POINT_COLOR;
	drawList->AddCircle(boxCenter, 4.0, color, 0, 2.0f);
}

bool Survive::BoxGizmos::isOver()
{
	return m_HoveredLine != -1 || m_CenterHovered;
}

void Survive::BoxGizmos::moveLine(const Camera &camera, BoxCollider2DComponent &boxCollider,
								  const glm::mat4 &modelMatrix, const glm::vec3 &position, float angle, int p1,
								  int p2, bool isVertical) const
{
	glm::vec3 mouseLocalPosition = getMouseLocalPosition(camera, modelMatrix, position);
	glm::vec3 offset = rotatePointAroundOrigin(mouseLocalPosition.x, mouseLocalPosition.y, -angle);

	b2Vec2 *points = boxCollider.boxShape.m_vertices;

	if (isVertical)
	{
		points[p1].x = offset.x;
		points[p2].x = offset.x;

		boxCollider.width = std::abs(points[0].x - points[1].x) / 2.0f;
	} else
	{
		points[p1].y = offset.y;
		points[p2].y = offset.y;

		boxCollider.height = std::abs(points[0].y - points[3].y) / 2.0f;
	}
}

void
Survive::BoxGizmos::moveCenter(const Camera &camera, BoxCollider2DComponent &boxCollider,
							   const glm::mat4 &modelMatrix, const glm::vec3 &position, float angle) const
{
	glm::vec3 boxCenter = getMouseLocalPosition(camera, modelMatrix, position);
	glm::vec3 rotatedCenter = rotatePointAroundOrigin(boxCenter.x, boxCenter.y, -angle);

	b2Vec2 &center = boxCollider.center;

	b2Vec2 diff = b2Vec2(rotatedCenter.x, rotatedCenter.y) - center;
	center = b2Vec2(rotatedCenter.x, rotatedCenter.y);

	EditorUtil::moveBoxCenter(boxCollider.boxShape.m_vertices, diff);
}

void
Survive::BoxGizmos::updateGizmos(const Camera &camera, BoxCollider2DComponent &boxCollider,
								 const Transform3DComponent &transform, const glm::mat4 &modelMatrix,
								 const std::vector<ImVec2> &points, const ImVec2 &center)
{
	updateLines(camera, boxCollider, transform, modelMatrix, points);
	updateCenter(center, camera, boxCollider, transform, modelMatrix);
}

void Survive::BoxGizmos::updateCenter(const ImVec2 &center, const Camera &camera, BoxCollider2DComponent &boxCollider,
									  const Transform3DComponent &transform, const glm::mat4 &modelMatrix)
{
	float angle = glm::radians(transform.rotation.z);

	if (!m_IsUsing && m_HoveredLine == -1 && Util::mouseHoversPoint(center, RADIUS))
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
		m_CenterHovered = true;
	} else if (!m_IsUsing)
	{
		m_CenterHovered = false;
	}

	if (m_CenterHovered && m_IsUsing)
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
		moveCenter(camera, boxCollider, modelMatrix, transform.position, angle);
	}
}

void Survive::BoxGizmos::updateLines(const Camera &camera, BoxCollider2DComponent &boxCollider,
									 const Transform3DComponent &transform, const glm::mat4 &modelMatrix,
									 const std::vector<ImVec2> &points)
{
	if (!m_IsUsing && !m_CenterHovered && Util::mouseHoversLine(points[0], points[1]))
	{
		m_HoveredLine = 0;
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	} else if (!m_IsUsing && !m_CenterHovered && Util::mouseHoversLine(points[1], points[2]))
	{
		m_HoveredLine = 1;
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	} else if (!m_IsUsing && !m_CenterHovered && Util::mouseHoversLine(points[2], points[3]))
	{
		m_HoveredLine = 2;
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	} else if (!m_IsUsing && !m_CenterHovered && Util::mouseHoversLine(points[3], points[0]))
	{
		m_HoveredLine = 3;
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	} else if (!m_IsUsing)
	{
		m_HoveredLine = -1;
		ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
	}

	float angle = glm::radians(transform.rotation.z);
	if (m_HoveredLine == 0 && m_IsUsing)
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
		moveLine(camera, boxCollider, modelMatrix, transform.position, angle, 0, 1, false);
	} else if (m_HoveredLine == 1 && m_IsUsing)
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
		moveLine(camera, boxCollider, modelMatrix, transform.position, angle, 1, 2, true);
	} else if (m_HoveredLine == 2 && m_IsUsing)
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
		moveLine(camera, boxCollider, modelMatrix, transform.position, angle, 2, 3, false);
	} else if (m_HoveredLine == 3 && m_IsUsing)
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
		moveLine(camera, boxCollider, modelMatrix, transform.position, angle, 3, 0, true);
	}
}

ImVec2 Survive::BoxGizmos::calcCenter(const b2Vec2 &localCenter, const Camera &camera, const glm::vec3 &position,
									  const glm::mat4 &modelMatrix, float angle) const
{
	glm::vec3 point = rotatePointAroundOrigin(localCenter.x, localCenter.y, angle);
	b2Vec2 center(point.x, point.y);

	return Util::getCenter(center, camera, position, modelMatrix, m_X, m_Y, m_Width, m_Height);
}

