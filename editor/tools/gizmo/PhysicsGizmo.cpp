//
// Created by david on 24. 10. 2021..
//

#include <imgui.h>
#include <imgui_internal.h>

#include "PhysicsGizmo.h"
#include "Maths.h"

void Survive::PhysicsGizmo::draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity) const
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

void Survive::PhysicsGizmo::drawBoxColliderGizmo(const Camera &camera, BoxCollider2DComponent &boxCollider,
												 const Transform3DComponent &transform,
												 const glm::mat4 &modelMatrix) const
{
	initializeBoxCollider(boxCollider, transform);

	auto[p1, p2, p3, p4] = getRectanglePoints(boxCollider, transform, camera, modelMatrix);

	drawRect(p1, p2, p3, p4, IM_COL32(255, 255, 255, 255), IM_COL32(0, 0, 255, 255));
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

	float width = boxCollider.width / Constants::BOX2D_SCALE;
	float height = boxCollider.height / Constants::BOX2D_SCALE;

	ImVec2 p1 = getScreenPos(camera, modelMatrix, {center.x - width, center.y + height, 0});
	ImVec2 p2 = getScreenPos(camera, modelMatrix, {center.x + width, center.y + height, 0});
	ImVec2 p3 = getScreenPos(camera, modelMatrix, {center.x + width, center.y - height, 0});
	ImVec2 p4 = getScreenPos(camera, modelMatrix, {center.x - width, center.y - height, 0});

	return {p1, p2, p3, p4};
}

void
Survive::PhysicsGizmo::drawRect(const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, const ImVec2 &p4, ImU32 rectColor,
								ImU32 circleColor)
{
	static constexpr float lineThickness = 2.0f;
	static constexpr float circleThickness = 4.0f;

	ImDrawList *drawList = ImGui::GetWindowDrawList();

	drawList->AddRect(p1, p3, rectColor, 0.0f, ImDrawFlags_None, lineThickness);

	drawList->AddCircleFilled(p1, circleThickness, circleColor);
	drawList->AddCircleFilled(p2, circleThickness, circleColor);
	drawList->AddCircleFilled(p3, circleThickness, circleColor);
	drawList->AddCircleFilled(p4, circleThickness, circleColor);
}

glm::vec2 Survive::PhysicsGizmo::getBoxCenter(const BoxCollider2DComponent &boxCollider,
											  const Transform3DComponent &transform)
{
	b2Vec2 boxCenter = boxCollider.center;
	glm::vec2 center{boxCenter.x / Constants::BOX2D_SCALE, boxCenter.y / Constants::BOX2D_SCALE};

	return glm::vec2{transform.position} + center;
}
