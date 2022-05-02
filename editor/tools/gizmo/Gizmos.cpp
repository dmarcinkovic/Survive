//
// Created by david on 05. 08. 2021..
//

#include <glm/gtc/type_ptr.hpp>

#include "Maths.h"
#include "Render2DComponent.h"
#include "Render3DComponent.h"
#include "TextComponent.h"
#include "Gizmos.h"
#include "Scene.h"

bool Survive::Gizmos::validOperation = false;

void Survive::Gizmos::draw(entt::registry &registry, Camera &camera, entt::entity selectedEntity)
{
	if (selectedEntity == entt::null)
	{
		validOperation = false;
	}

	if (validOperation && registry.any_of<Transform3DComponent>(selectedEntity))
	{
		if (registry.any_of<Render3DComponent>(selectedEntity))
		{
			drawGizmos(false, camera.getProjectionMatrix(), camera.getViewMatrix(), registry, selectedEntity);
		} else if (registry.any_of<Render2DComponent>(selectedEntity) || registry.any_of<TextComponent>(selectedEntity))
		{
			drawGizmos(true, camera.getOrthographicProjectionMatrix(), glm::mat4{1.0f}, registry,
					   selectedEntity);
		}
	}

	drawViewGizmos(camera);

	m_Gizmos.draw(registry, camera, selectedEntity);
}

void Survive::Gizmos::newFrame()
{
	ImGuizmo::BeginFrame();
}

void Survive::Gizmos::handleKeyEvents(const EventHandler &eventHandler)
{
	if (!m_Gizmos.isEnabled())
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

	if (!validOperation)
	{
		m_Gizmos.handleKeyEvents(eventHandler);
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
								 entt::registry &registry, entt::entity entity) const
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

void Survive::Gizmos::drawViewGizmos(Camera &camera) const
{
	ImGuizmo::SetDrawlist();
	ImGuizmo::SetRect(m_X, m_Y, m_Width, m_Height);

	const float cameraDistance = 8.0f;

	float textHeight = ImGui::GetTextLineHeight();
	ImVec2 size{10.0f * textHeight, 10.0f * textHeight};
	ImU32 backgroundColor = 0x10101010;

	auto [sceneX, sceneY] = Scene::getScenePosition();
	float sceneWidth = Scene::getSceneWidth();
	ImVec2 position{sceneX + sceneWidth - size.x, sceneY};

	glm::mat4 &viewMatrix = camera.getViewMatrix();
	ImGuizmo::ViewManipulate(glm::value_ptr(viewMatrix), cameraDistance, position, size, backgroundColor);

	decomposeViewMatrix(camera, viewMatrix);
}

void Survive::Gizmos::decomposeViewMatrix(Camera &camera, const glm::mat4 &viewMatrix)
{
	glm::mat4 inverseViewMatrix = glm::inverse(viewMatrix);
	const glm::vec3 direction = glm::vec3{inverseViewMatrix[2]};

	float pitch = glm::degrees(glm::asin(direction.y));
	float yaw = 90.0f - glm::degrees(glm::atan(direction.z, direction.x));
	glm::vec3 cameraPosition = glm::vec3{inverseViewMatrix[3]};

	camera.setCameraProperties(pitch, yaw, cameraPosition);
}
