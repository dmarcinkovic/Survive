//
// Created by david on 05. 08. 2021..
//

#include <glm/gtc/type_ptr.hpp>

#include "Transform3DComponent.h"
#include "Gizmos.h"
#include "Maths.h"

Survive::Gizmos::Gizmos()
{
	ImGuizmo::SetOrthographic(false);
}

void Survive::Gizmos::draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity) const
{
	if (selectedEntity != entt::null && registry.has<Transform3DComponent>(selectedEntity))
	{
		ImGuizmo::SetDrawlist();
		ImGuizmo::SetRect(m_X, m_Y, m_Width, m_Height);

		glm::mat4 viewMatrix = camera.getViewMatrix();
		glm::mat4 projectionMatrix = camera.getProjectionMatrix();

		Transform3DComponent &transformComponent = registry.get<Transform3DComponent>(selectedEntity);
		glm::mat4 transform = Maths::recomposeMatrixFromComponents(transformComponent.position,
																   transformComponent.scale,
																   transformComponent.rotation);

		float *matrix = glm::value_ptr(transform);
		ImGuizmo::Manipulate(glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix),
							 ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::LOCAL, matrix);

		if (ImGuizmo::IsUsing())
		{
			glm::vec3 translation, rotation, scale;
			ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transform), glm::value_ptr(translation),
												  glm::value_ptr(rotation), glm::value_ptr(scale));

			transformComponent.position = translation;
			transformComponent.rotation = rotation;
			transformComponent.scale = scale;
		}
	}
}

void Survive::Gizmos::newFrame()
{
	ImGuizmo::BeginFrame();
}

void Survive::Gizmos::handleKeyEvents(const EventHandler &eventHandler)
{

}

void Survive::Gizmos::setRect(float x, float y, float width, float height)
{
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;
}
