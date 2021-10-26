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

glm::vec2 Survive::PhysicsGizmo::getScreenPos(const Survive::Camera &camera, const glm::mat4 &transformationMatrix,
											  const glm::vec3 &point) const
{
	glm::mat4 projectionMatrix = camera.getOrthographicProjectionMatrix();
	glm::vec4 clipSpace = glm::vec4(point, 1) * transformationMatrix * projectionMatrix;

	glm::vec3 normalizedDeviceSpace{clipSpace};
	glm::vec3 viewportSpace = normalizedDeviceSpace * 0.5f + 0.5f;

	return glm::vec2{m_X + viewportSpace.x * m_Width, m_Y + m_Height - viewportSpace.y * m_Height};
}

void Survive::PhysicsGizmo::drawBoxColliderGizmo(const Camera &camera, BoxCollider2DComponent &boxCollider,
												 const Survive::Transform3DComponent &transform,
												 const glm::mat4 &modelMatrix) const
{
	const float scale = Constants::BOX2D_SCALE;

	if (!boxCollider.m_Initialized)
	{
		boxCollider.width = transform.scale.x * scale;
		boxCollider.height = transform.scale.y * scale;
		boxCollider.boxShape.SetAsBox(boxCollider.width, boxCollider.height);

		boxCollider.m_Initialized = true;
	}

	b2Vec2 boxCenter = boxCollider.center;
	glm::vec2 center = glm::vec2{transform.position.x, transform.position.y} +
					   glm::vec2{boxCenter.x / scale, boxCenter.y / scale};

	float width = boxCollider.width / scale;
	float height = boxCollider.height / scale;
	glm::vec3 p1{center.x - width, center.y + height, 0};
	glm::vec3 p2{center.x + width, center.y + height, 0};
	glm::vec3 p3{center.x + width, center.y - height, 0};
	glm::vec3 p4{center.x - width, center.y - height, 0};

	glm::vec2 screenP1 = getScreenPos(camera, modelMatrix, p1);
	glm::vec2 screenP2 = getScreenPos(camera, modelMatrix, p2);
	glm::vec2 screenP3 = getScreenPos(camera, modelMatrix, p3);
	glm::vec2 screenP4 = getScreenPos(camera, modelMatrix, p4);

	ImDrawList *drawList = ImGui::GetWindowDrawList();
	drawList->AddRect(ImVec2(screenP1.x, screenP1.y), ImVec2(screenP3.x, screenP3.y), IM_COL32(255, 255, 255, 255),
					  0.0f, ImDrawFlags_None, 2.0f);

	drawList->AddCircleFilled(ImVec2(screenP1.x, screenP1.y), 4.0f, IM_COL32(0, 0, 255, 255));
	drawList->AddCircleFilled(ImVec2(screenP2.x, screenP2.y), 4.0f, IM_COL32(0, 0, 255, 255));
	drawList->AddCircleFilled(ImVec2(screenP3.x, screenP3.y), 4.0f, IM_COL32(0, 0, 255, 255));
	drawList->AddCircleFilled(ImVec2(screenP4.x, screenP4.y), 4.0f, IM_COL32(0, 0, 255, 255));
}
