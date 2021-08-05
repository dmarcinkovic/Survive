//
// Created by david on 05. 08. 2021..
//

#include <glm/gtc/type_ptr.hpp>

#include "Gizmos.h"
#include "Maths.h"

Survive::Gizmos::Gizmos()
{
	ImGuizmo::SetOrthographic(false);
}

void Survive::Gizmos::draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity) const
{
	if (m_DrawGizmos && selectedEntity != entt::null && registry.has<Transform3DComponent>(selectedEntity))
	{
		ImGuizmo::SetDrawlist();
		ImGuizmo::SetRect(m_X, m_Y, m_Width, m_Height);

		glm::mat4 viewMatrix = camera.getViewMatrix();
		glm::mat4 projectionMatrix = camera.getProjectionMatrix();

		Transform3DComponent &transformComponent = registry.get<Transform3DComponent>(selectedEntity);
		glm::mat4 transform = getTransform(transformComponent);

		float *matrix = glm::value_ptr(transform);
		ImGuizmo::Manipulate(glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix),
							 m_Operation, ImGuizmo::LOCAL, matrix);

		useGizmo(transformComponent, transform);
	}
}

void Survive::Gizmos::newFrame()
{
	ImGuizmo::BeginFrame();
}

void Survive::Gizmos::handleKeyEvents(const EventHandler &eventHandler)
{
	if (eventHandler.isKeyPressed(Key::W))
	{
		m_Operation = ImGuizmo::OPERATION::TRANSLATE;
		m_DrawGizmos = true;
	} else if (eventHandler.isKeyPressed(Key::E))
	{
		m_Operation = ImGuizmo::OPERATION::ROTATE;
		m_DrawGizmos = true;
	} else if (eventHandler.isKeyPressed(Key::R))
	{
		m_Operation = ImGuizmo::OPERATION::SCALE;
		m_DrawGizmos = true;
	}
}

void Survive::Gizmos::setRect(float x, float y, float width, float height)
{
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;
}

glm::mat4 Survive::Gizmos::getTransform(const Survive::Transform3DComponent &transform)
{
	return Maths::recomposeMatrixFromComponents(transform.position, transform.scale, transform.rotation);
}

void Survive::Gizmos::useGizmo(Survive::Transform3DComponent &transformComponent, glm::mat4 &transform)
{
	if (ImGuizmo::IsUsing())
	{
		ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transform),
											  glm::value_ptr(transformComponent.position),
											  glm::value_ptr(transformComponent.rotation),
											  glm::value_ptr(transformComponent.scale));
	}
}
