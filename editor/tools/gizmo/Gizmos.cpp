//
// Created by david on 05. 08. 2021..
//

#include <glm/gtc/type_ptr.hpp>

#include "Maths.h"
#include "Render2DComponent.h"
#include "Render3DComponent.h"
#include "TextComponent.h"
#include "Gizmos.h"

bool Survive::Gizmos::validOperation = false;

void Survive::Gizmos::draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity) const
{
	if (validOperation && selectedEntity != entt::null && registry.any_of<Transform3DComponent>(selectedEntity))
	{
		if (registry.any_of<Render3DComponent>(selectedEntity))
		{
			drawGizmos(false, camera.getProjectionMatrix(), camera.getViewMatrix(), camera, registry, selectedEntity);
		} else if (registry.any_of<Render2DComponent>(selectedEntity) || registry.any_of<TextComponent>(selectedEntity))
		{
			drawGizmos(true, camera.getOrthographicProjectionMatrix(), glm::mat4{1.0f}, camera, registry,
					   selectedEntity);
		}
	}

	m_Gizmos.draw(registry, camera, selectedEntity);
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
		validOperation = true;
	} else if (eventHandler.isKeyPressed(Key::E))
	{
		m_Operation = ImGuizmo::OPERATION::ROTATE;
		validOperation = true;
	} else if (eventHandler.isKeyPressed(Key::R))
	{
		m_Operation = ImGuizmo::OPERATION::SCALE;
		validOperation = true;
	} else if (eventHandler.isKeyPressed(Key::ESCAPE))
	{
		validOperation = false;
	}
}

void Survive::Gizmos::setRect(float x, float y, float width, float height)
{
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;

	m_Gizmos.setRect(x, y, width, height);
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

bool Survive::Gizmos::isValidOperation()
{
	return validOperation;
}

void Survive::Gizmos::drawGizmos(bool isOrthographic, const glm::mat4 &projectionMatrix, const glm::mat4 &viewMatrix,
								 const Camera &camera, entt::registry &registry, entt::entity entity) const
{
	ImGuizmo::SetOrthographic(isOrthographic);

	ImGuizmo::SetDrawlist();
	ImGuizmo::SetRect(m_X, m_Y, m_Width, m_Height);

	Transform3DComponent &transformComponent = registry.get<Transform3DComponent>(entity);
	glm::mat4 transform = getTransform(transformComponent);

	float *matrix = glm::value_ptr(transform);
	ImGuizmo::Manipulate(glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix),
						 m_Operation, ImGuizmo::LOCAL, matrix);

	useGizmo(transformComponent, transform);
}
