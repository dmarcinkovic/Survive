//
// Created by david on 24. 10. 2021..
//

#include <imgui.h>
#include <imgui_internal.h>
#include <iostream>

#include "PhysicsGizmo.h"
#include "Maths.h"

void Survive::PhysicsGizmo::draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity)
{
	if (selectedEntity != entt::null &&
		registry.all_of<BoxCollider2DComponent, Transform3DComponent, Render2DComponent>(selectedEntity))
	{
		BoxCollider2DComponent &boxCollider = registry.get<BoxCollider2DComponent>(selectedEntity);
		const Transform3DComponent &transform = registry.get<Transform3DComponent>(selectedEntity);

		glm::mat4 transformationMatrix = Maths::createTransformationMatrix(transform.position);

		drawBoxColliderGizmo(camera, boxCollider, transform, transformationMatrix);
	}
}

void Survive::PhysicsGizmo::handleKeyEvents(const EventHandler &eventHandler)
{
}

void Survive::PhysicsGizmo::setRect(float x, float y, float width, float height)
{
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;
}

ImVec2 Survive::PhysicsGizmo::getScreenPos(const Survive::Camera &camera, const glm::mat4 &transformationMatrix,
										   const glm::vec3 &point) const
{
	glm::mat4 projectionMatrix = camera.getOrthographicProjectionMatrix();
	glm::vec4 clipSpace = glm::vec4(point, 1) * transformationMatrix * projectionMatrix;

	glm::vec3 normalizedDeviceSpace{clipSpace};
	glm::vec3 viewportSpace = normalizedDeviceSpace * 0.5f + 0.5f;

	return {m_X + viewportSpace.x * m_Width, m_Y + m_Height - viewportSpace.y * m_Height};
}

glm::vec3 Survive::PhysicsGizmo::getLocalSpace(const Camera &camera, const glm::mat4 &transformationMatrix,
											   const ImVec2 &point) const
{
	glm::mat4 projectionMatrix = camera.getOrthographicProjectionMatrix();

	ImVec2 screenPos(point.x - m_X, point.y - m_Y);
	glm::vec2 viewport{screenPos.x / m_Width, 1.0f - screenPos.y / m_Height};

	glm::vec4 clipSpace{viewport * 2.0f - 1.0f, 0.0f, 1.0f};
	glm::vec4 localSpace = clipSpace * glm::inverse(projectionMatrix) * glm::inverse(transformationMatrix);

	return glm::vec3{localSpace};
}

void Survive::PhysicsGizmo::drawBoxColliderGizmo(const Camera &camera, BoxCollider2DComponent &boxCollider,
												 const Transform3DComponent &transform,
												 const glm::mat4 &modelMatrix)
{
	initializeBoxCollider(boxCollider, transform);

	auto[p1, p2, p3, p4] = getRectanglePoints(boxCollider, transform, camera, modelMatrix);

	m_HoveredLine = -1;
	if (mouseHoversLine(p1, p2))
	{
		m_HoveredLine = 0;
		if ((m_Using = ImGui::IsMouseDragging(ImGuiMouseButton_Left)))
		{
			ImVec2 mousePosition = ImGui::GetMousePos();
			glm::vec3 localPos = getLocalSpace(camera, modelMatrix, mousePosition);

			float offset = transform.position.y * Constants::BOX2D_SCALE;

			localPos *= Constants::BOX2D_SCALE;
			b2Vec2 *points = boxCollider.boxShape.m_vertices;

			points[0].y = localPos.y - offset;
			points[1].y = localPos.y - offset;

			boxCollider.height = std::abs(points[0].y - points[3].y) / 2.0f;
		}
	} else if (mouseHoversLine(p2, p3))
	{
		m_HoveredLine = 1;
		if ((m_Using = ImGui::IsMouseDragging(ImGuiMouseButton_Left)))
		{
			ImVec2 mousePosition = ImGui::GetMousePos();
			glm::vec3 localPos = getLocalSpace(camera, modelMatrix, mousePosition);

			float offset = transform.position.x * Constants::BOX2D_SCALE;

			localPos *= Constants::BOX2D_SCALE;
			b2Vec2 *points = boxCollider.boxShape.m_vertices;
			points[1].x = localPos.x - offset;
			points[2].x = localPos.x - offset;

			boxCollider.width = std::abs(points[0].x - points[1].x) / 2.0f;
		}
	} else if (mouseHoversLine(p3, p4))
	{
		m_HoveredLine = 2;
		if ((m_Using = ImGui::IsMouseDragging(ImGuiMouseButton_Left)))
		{
			ImVec2 mousePosition = ImGui::GetMousePos();
			glm::vec3 localPos = getLocalSpace(camera, modelMatrix, mousePosition);

			float offset = transform.position.y * Constants::BOX2D_SCALE;

			localPos *= Constants::BOX2D_SCALE;
			b2Vec2 *points = boxCollider.boxShape.m_vertices;
			points[2].y = localPos.y - offset;
			points[3].y = localPos.y - offset;

			boxCollider.height = std::abs(points[0].y - points[3].y) / 2.0f;
		}
	} else if (mouseHoversLine(p4, p1))
	{
		m_HoveredLine = 3;
		if ((m_Using = ImGui::IsMouseDragging(ImGuiMouseButton_Left)))
		{
			ImVec2 mousePosition = ImGui::GetMousePos();
			glm::vec3 localPos = getLocalSpace(camera, modelMatrix, mousePosition);

			float offset = transform.position.x * Constants::BOX2D_SCALE;

			localPos *= Constants::BOX2D_SCALE;
			b2Vec2 *points = boxCollider.boxShape.m_vertices;
			points[3].x = localPos.x - offset;
			points[0].x = localPos.x - offset;

			boxCollider.width = std::abs(points[0].x - points[1].x) / 2.0f;
		}
	}

	drawRect(p1, p2, p3, p4, m_HoveredLine);
}

void Survive::PhysicsGizmo::initializeBoxCollider(BoxCollider2DComponent &boxCollider,
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
Survive::PhysicsGizmo::getRectanglePoints(const BoxCollider2DComponent &boxCollider,
										  const Transform3DComponent &transform, const Camera &camera,
										  const glm::mat4 &modelMatrix) const
{
	glm::vec2 center = getBoxCenter(boxCollider, transform);

	float scale = Constants::BOX2D_SCALE;
	const b2Vec2 *vertices = boxCollider.boxShape.m_vertices;
	glm::vec2 offset = transform.position;

	// TODO change this
	ImVec2 p1 = getScreenPos(camera, modelMatrix,
							 {vertices[0].x / scale + offset.x, vertices[0].y / scale + offset.y, 0});
	ImVec2 p2 = getScreenPos(camera, modelMatrix,
							 {vertices[1].x / scale + offset.x, vertices[1].y / scale + offset.y, 0});
	ImVec2 p3 = getScreenPos(camera, modelMatrix,
							 {vertices[2].x / scale + offset.x, vertices[2].y / scale + offset.y, 0});
	ImVec2 p4 = getScreenPos(camera, modelMatrix,
							 {vertices[3].x / scale + offset.x, vertices[3].y / scale + offset.y, 0});

	return {p1, p2, p3, p4};
}

void Survive::PhysicsGizmo::drawRect(const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, const ImVec2 &p4,
									 int hoveredLine)
{
	static constexpr float circleThickness = 4.0f;
	static constexpr ImU32 CIRCLE_COLOR = IM_COL32(0, 0, 255, 255);

	ImDrawList *drawList = ImGui::GetWindowDrawList();

	drawLine(drawList, p1, p2, hoveredLine == 0);
	drawLine(drawList, p2, p3, hoveredLine == 1);
	drawLine(drawList, p3, p4, hoveredLine == 2);
	drawLine(drawList, p4, p1, hoveredLine == 3);

	drawList->AddCircleFilled(p1, circleThickness, CIRCLE_COLOR);
	drawList->AddCircleFilled(p2, circleThickness, CIRCLE_COLOR);
	drawList->AddCircleFilled(p3, circleThickness, CIRCLE_COLOR);
	drawList->AddCircleFilled(p4, circleThickness, CIRCLE_COLOR);
}

glm::vec2 Survive::PhysicsGizmo::getBoxCenter(const BoxCollider2DComponent &boxCollider,
											  const Transform3DComponent &transform)
{
	b2Vec2 boxCenter = boxCollider.center;
	glm::vec2 center{boxCenter.x / Constants::BOX2D_SCALE, boxCenter.y / Constants::BOX2D_SCALE};

	return glm::vec2{transform.position} + center;
}

bool Survive::PhysicsGizmo::mouseHoversLine(const ImVec2 &p1, const ImVec2 &p2)
{
	static float constexpr threshold = 3;
	ImVec2 mousePosition = ImGui::GetMousePos();

	float lineLen = lineDistance(p1, p2);

	float segmentLen1 = lineDistance(p1, mousePosition);
	float segmentLen2 = lineDistance(p2, mousePosition);

	return segmentLen1 + segmentLen2 - lineLen < threshold;
}

float Survive::PhysicsGizmo::lineDistance(const ImVec2 &p1, const ImVec2 &p2)
{
	float dx = p1.x - p2.x;
	float dy = p1.y - p2.y;

	return std::sqrt(dx * dx + dy * dy);
}

bool Survive::PhysicsGizmo::isUsing() const
{
	return m_Using;
}

void Survive::PhysicsGizmo::drawLine(ImDrawList *drawList, const ImVec2 &p1, const ImVec2 &p2, bool isHovered)
{
	static constexpr float lineThickness = 2.0f;
	static constexpr ImU32 LINE_COLOR = IM_COL32(255, 255, 255, 255);
	static constexpr ImU32 LINE_COLOR_HOVERED = IM_COL32(255, 90, 0, 255);

	ImU32 color = isHovered ? LINE_COLOR_HOVERED : LINE_COLOR;
	drawList->AddLine(p1, p2, color, lineThickness);
}
