//
// Created by david on 31. 10. 2021..
//

#include <imgui.h>

#include "Maths.h"
#include "BoxGizmos.h"
#include "Util.h"
#include "EditorUtil.h"

int Survive::BoxGizmos::m_HoveredLine = -1;
bool Survive::BoxGizmos::m_CenterHovered{};

void Survive::BoxGizmos::draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity)
{
	if (m_GizmoEnabled && selectedEntity != entt::null &&
		registry.all_of<BoxCollider2DComponent, Transform3DComponent, Render2DComponent>(selectedEntity))
	{
		BoxCollider2DComponent &boxCollider = registry.get<BoxCollider2DComponent>(selectedEntity);
		const Transform3DComponent &transform = registry.get<Transform3DComponent>(selectedEntity);

		glm::mat4 transformationMatrix = Maths::createTransformationMatrix(transform.position);

		drawBoxColliderGizmo(camera, boxCollider, transform, transformationMatrix);
	}
}

void Survive::BoxGizmos::handleKeyEvents(const EventHandler &eventHandler)
{
	if (eventHandler.isKeyPressed(Key::A))
	{
		m_GizmoEnabled = true;
	} else if (eventHandler.isKeyPressed(Key::ESCAPE))
	{
		m_GizmoEnabled = false;
	}
}

void Survive::BoxGizmos::setRect(float x, float y, float width, float height)
{
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;
}

void Survive::BoxGizmos::drawBoxColliderGizmo(const Camera &camera, BoxCollider2DComponent &boxCollider,
											  const Transform3DComponent &transform,
											  const glm::mat4 &modelMatrix)
{
	initializeBoxCollider(boxCollider, transform);

	ImVec2 center = getBoxCenter(boxCollider, camera, transform, modelMatrix);

	m_IsUsing = ImGui::IsMouseDragging(ImGuiMouseButton_Left);

	auto[p1, p2, p3, p4] = getRectanglePoints(boxCollider, transform, camera, modelMatrix);
	drawHoveredLines(camera, boxCollider, transform, modelMatrix, p1, p2, p3, p4);

	if (!m_IsUsing && Util::mouseHoversPoint(center, RADIUS))
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
		drawHoveredPoint(camera, boxCollider, modelMatrix, transform.position);
	}

	drawRect(p1, p2, p3, p4, m_HoveredLine);
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

std::tuple<ImVec2, ImVec2, ImVec2, ImVec2>
Survive::BoxGizmos::getRectanglePoints(const BoxCollider2DComponent &boxCollider,
									   const Transform3DComponent &transform, const Camera &camera,
									   const glm::mat4 &modelMatrix) const
{
	float scale = Constants::BOX2D_SCALE;
	const b2Vec2 *vertices = boxCollider.boxShape.m_vertices;

	glm::vec2 offset = transform.position;

	glm::vec2 vertex1{vertices[0].x / scale, vertices[0].y / scale};
	glm::vec2 vertex2{vertices[1].x / scale, vertices[1].y / scale};
	glm::vec2 vertex3{vertices[2].x / scale, vertices[2].y / scale};
	glm::vec2 vertex4{vertices[3].x / scale, vertices[3].y / scale};

	ImVec2 p1 = Util::getScreenPos(camera, modelMatrix, vertex1 + offset, m_X, m_Y, m_Width, m_Height);
	ImVec2 p2 = Util::getScreenPos(camera, modelMatrix, vertex2 + offset, m_X, m_Y, m_Width, m_Height);
	ImVec2 p3 = Util::getScreenPos(camera, modelMatrix, vertex3 + offset, m_X, m_Y, m_Width, m_Height);
	ImVec2 p4 = Util::getScreenPos(camera, modelMatrix, vertex4 + offset, m_X, m_Y, m_Width, m_Height);

	return {p1, p2, p3, p4};
}

void Survive::BoxGizmos::drawRect(const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3,
								  const ImVec2 &p4, int hoveredLine)
{
	static constexpr float CIRCLE_RADIUS = 5.0f;
	static constexpr ImU32 CIRCLE_COLOR = IM_COL32(0, 0, 255, 255);

	ImDrawList *drawList = ImGui::GetWindowDrawList();

	drawLine(drawList, p1, p2, hoveredLine == 0);
	drawLine(drawList, p2, p3, hoveredLine == 1);
	drawLine(drawList, p3, p4, hoveredLine == 2);
	drawLine(drawList, p4, p1, hoveredLine == 3);

	drawList->AddCircleFilled(p1, CIRCLE_RADIUS, CIRCLE_COLOR);
	drawList->AddCircleFilled(p2, CIRCLE_RADIUS, CIRCLE_COLOR);
	drawList->AddCircleFilled(p3, CIRCLE_RADIUS, CIRCLE_COLOR);
	drawList->AddCircleFilled(p4, CIRCLE_RADIUS, CIRCLE_COLOR);
}

ImVec2 Survive::BoxGizmos::getBoxCenter(const BoxCollider2DComponent &boxCollider, const Camera &camera,
										const Transform3DComponent &transform, const glm::mat4 &modelMatrix) const
{
	b2Vec2 boxCenter = boxCollider.center;

	float scale = Constants::BOX2D_SCALE;
	glm::vec2 center{boxCenter.x / scale, boxCenter.y / scale};
	glm::vec2 point{center.x + transform.position.x, center.y + transform.position.y};

	return Util::getScreenPos(camera, modelMatrix, point, m_X, m_Y, m_Width, m_Height);
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

void Survive::BoxGizmos::drawHoveredLine(const Camera &camera, BoxCollider2DComponent &boxCollider,
										 const glm::mat4 &modelMatrix, float offset, int p1, int p2,
										 bool isVertical) const
{
	ImVec2 mousePosition = ImGui::GetMousePos();
	glm::vec3 localPos = Util::getLocalSpace(camera, modelMatrix, mousePosition, m_X, m_Y, m_Width, m_Height);

	float offsetBox2D = offset * Constants::BOX2D_SCALE;
	localPos *= Constants::BOX2D_SCALE;

	b2Vec2 *points = boxCollider.boxShape.m_vertices;

	if (isVertical)
	{
		points[p1].x = localPos.x - offsetBox2D;
		points[p2].x = localPos.x - offsetBox2D;

		boxCollider.width = std::abs(points[0].x - points[1].x) / 2.0f;
	} else
	{
		points[p1].y = localPos.y - offsetBox2D;
		points[p2].y = localPos.y - offsetBox2D;

		boxCollider.height = std::abs(points[0].y - points[3].y) / 2.0f;
	}
}

void
Survive::BoxGizmos::drawHoveredPoint(const Survive::Camera &camera, Survive::BoxCollider2DComponent &boxCollider,
									 const glm::mat4 &modelMatrix, const glm::vec3 &position) const
{
	ImVec2 mousePosition = ImGui::GetMousePos();
	glm::vec3 localPos = Util::getLocalSpace(camera, modelMatrix, mousePosition, m_X, m_Y, m_Width, m_Height);

	glm::vec3 offset = position * Constants::BOX2D_SCALE;
	localPos *= Constants::BOX2D_SCALE;

	glm::vec3 boxCenter = localPos - offset;
	b2Vec2 oldCenter = boxCollider.center;
	boxCollider.center = b2Vec2(boxCenter.x, boxCenter.y);

	EditorUtil::moveBoxCenter(boxCollider.boxShape.m_vertices, boxCollider.center - oldCenter);
}

void
Survive::BoxGizmos::drawHoveredLines(const Camera &camera, BoxCollider2DComponent &boxCollider,
									 const Transform3DComponent &transform, const glm::mat4 &modelMatrix,
									 const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, const ImVec2 &p4)
{
	if (!m_IsUsing && Util::mouseHoversLine(p1, p2))
	{
		m_HoveredLine = 0;
		ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);
	} else if (!m_IsUsing && Util::mouseHoversLine(p2, p3))
	{
		m_HoveredLine = 1;
		ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
	} else if (!m_IsUsing && Util::mouseHoversLine(p3, p4))
	{
		m_HoveredLine = 2;
		ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);
	} else if (!m_IsUsing && Util::mouseHoversLine(p4, p1))
	{
		m_HoveredLine = 3;
		ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
	} else if (!m_IsUsing)
	{
		m_HoveredLine = -1;
		ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
	}

	if (m_HoveredLine == 0 && m_IsUsing)
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);
		drawHoveredLine(camera, boxCollider, modelMatrix, transform.position.y, 0, 1, false);
	} else if (m_HoveredLine == 1 && m_IsUsing)
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
		drawHoveredLine(camera, boxCollider, modelMatrix, transform.position.x, 1, 2, true);
	} else if (m_HoveredLine == 2 && m_IsUsing)
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);
		drawHoveredLine(camera, boxCollider, modelMatrix, transform.position.y, 2, 3, false);
	} else if (m_HoveredLine == 3 && m_IsUsing)
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
		drawHoveredLine(camera, boxCollider, modelMatrix, transform.position.x, 3, 0, true);
	}
}
