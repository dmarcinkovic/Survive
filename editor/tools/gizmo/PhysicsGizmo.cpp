//
// Created by david on 24. 10. 2021..
//

#include <imgui.h>

#include "PhysicsGizmo.h"
#include "Maths.h"

void Survive::PhysicsGizmo::draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity)
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

void Survive::PhysicsGizmo::handleKeyEvents(const EventHandler &eventHandler)
{
	if (eventHandler.isKeyPressed(Key::A))
	{
		m_GizmoEnabled = true;
	} else if (eventHandler.isKeyPressed(Key::ESCAPE))
	{
		m_GizmoEnabled = false;
	}
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

	const float radius = 4.0f;
	ImVec2 center = getBoxCenter(boxCollider, camera, transform, modelMatrix);

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
	} else if ((m_CenterHovered = mouseHoversPoint(center, radius)))
	{
		if ((m_Using = ImGui::IsMouseDragging(ImGuiMouseButton_Left)))
		{
			ImVec2 mousePosition = ImGui::GetMousePos();
			glm::vec3 localPos = getLocalSpace(camera, modelMatrix, mousePosition);

			glm::vec3 offset = transform.position * Constants::BOX2D_SCALE;
			localPos *= Constants::BOX2D_SCALE;

			glm::vec3 boxCenter = localPos - offset;
			boxCollider.center = b2Vec2(boxCenter.x, boxCenter.y);
		}
	}

	drawRect(p1, p2, p3, p4, m_HoveredLine);
	drawCenter(center, radius, m_CenterHovered);
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
	float scale = Constants::BOX2D_SCALE;
	const b2Vec2 *vertices = boxCollider.boxShape.m_vertices;

	glm::vec2 offset = transform.position;

	glm::vec2 vertex1{vertices[0].x / scale, vertices[0].y / scale};
	glm::vec2 vertex2{vertices[1].x / scale, vertices[1].y / scale};
	glm::vec2 vertex3{vertices[2].x / scale, vertices[2].y / scale};
	glm::vec2 vertex4{vertices[3].x / scale, vertices[3].y / scale};

	ImVec2 p1 = getScreenPos(camera, modelMatrix, vertex1 + offset);
	ImVec2 p2 = getScreenPos(camera, modelMatrix, vertex2 + offset);
	ImVec2 p3 = getScreenPos(camera, modelMatrix, vertex3 + offset);
	ImVec2 p4 = getScreenPos(camera, modelMatrix, vertex4 + offset);

	return {p1, p2, p3, p4};
}

void Survive::PhysicsGizmo::drawRect(const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3,
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

ImVec2 Survive::PhysicsGizmo::getBoxCenter(const BoxCollider2DComponent &boxCollider, const Camera &camera,
										   const Transform3DComponent &transform, const glm::mat4 &modelMatrix) const
{
	b2Vec2 boxCenter = boxCollider.center;

	float scale = Constants::BOX2D_SCALE;
	glm::vec2 center{boxCenter.x / scale, boxCenter.y / scale};
	glm::vec2 point{center.x + transform.position.x, center.y + transform.position.y};

	return getScreenPos(camera, modelMatrix, point);
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
	static constexpr float LINE_THICKNESS = 2.0f;
	static constexpr ImU32 LINE_COLOR = IM_COL32(255, 255, 255, 255);
	static constexpr ImU32 LINE_COLOR_HOVERED = IM_COL32(255, 90, 0, 255);

	ImU32 color = isHovered ? LINE_COLOR_HOVERED : LINE_COLOR;
	drawList->AddLine(p1, p2, color, LINE_THICKNESS);
}

ImVec2 Survive::PhysicsGizmo::getScreenPos(const Survive::Camera &camera, const glm::mat4 &transformationMatrix,
										   const glm::vec2 &point) const
{
	return getScreenPos(camera, transformationMatrix, glm::vec3{point, 0.0f});
}

void Survive::PhysicsGizmo::drawCenter(const ImVec2 &boxCenter, float radius, bool isHovered)
{
	static constexpr ImU32 POINT_COLOR = IM_COL32(255, 255, 255, 255);
	static constexpr ImU32 POINT_COLOR_HOVERED = IM_COL32(255, 90, 0, 255);

	ImDrawList *drawList = ImGui::GetWindowDrawList();

	ImU32 color = isHovered ? POINT_COLOR_HOVERED : POINT_COLOR;
	drawList->AddCircle(boxCenter, radius, color, 0, 2.0f);
}

bool Survive::PhysicsGizmo::mouseHoversPoint(const ImVec2 &point, float radius)
{
	static constexpr float EPSILON = 4.0f;
	ImVec2 mousePos = ImGui::GetMousePos();

	return std::abs(mousePos.x - point.x) < radius + EPSILON &&
		   std::abs(mousePos.y - point.y) < radius + EPSILON;
}
