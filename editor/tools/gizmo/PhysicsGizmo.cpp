//
// Created by david on 24. 10. 2021..
//

#include <imgui.h>
#include <imgui_internal.h>
#include <iostream>

#include "Components.h"
#include "PhysicsGizmo.h"
#include "Maths.h"

void Survive::PhysicsGizmo::draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity) const
{
	if (selectedEntity != entt::null &&
		registry.all_of<BoxCollider2DComponent, Transform3DComponent, Render2DComponent>(selectedEntity))
	{
		BoxCollider2DComponent &boxCollider = registry.get<BoxCollider2DComponent>(selectedEntity);
		const Transform3DComponent &transform = registry.get<Transform3DComponent>(selectedEntity);

		ImDrawList *drawList = ImGui::GetWindowDrawList();

		glm::mat4 transformationMatrix = Maths::createTransformationMatrix(transform.position);
		glm::vec2 upperLeft = getScreenPos(camera, transformationMatrix, transform.position - transform.scale);
		glm::vec2 lowerRight = getScreenPos(camera, transformationMatrix, transform.position + transform.scale);

		drawList->AddRect(ImVec2(upperLeft.x, upperLeft.y), ImVec2(lowerRight.x, lowerRight.y),
						  IM_COL32(255, 0, 0, 255), 0, ImDrawFlags_None, 2.0f);
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
