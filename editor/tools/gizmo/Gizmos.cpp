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

bool Survive::Gizmos::m_ValidOperation = false;

void Survive::Gizmos::draw(entt::registry &registry, Camera &camera, entt::entity selectedEntity)
{
	if (selectedEntity == entt::null)
	{
		m_ValidOperation = false;
	}

	if (m_ValidOperation && registry.any_of<Transform3DComponent>(selectedEntity))
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
			m_ValidOperation = true;
		} else if (eventHandler.isKeyPressed(Key::E))
		{
			m_Operation = ImGuizmo::OPERATION::ROTATE;
			m_ValidOperation = true;
		} else if (eventHandler.isKeyPressed(Key::R))
		{
			m_Operation = ImGuizmo::OPERATION::SCALE;
			m_ValidOperation = true;
		} else if (eventHandler.isKeyPressed(Key::ESCAPE))
		{
			m_ValidOperation = false;
		}
	}

	if (!m_ValidOperation)
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
	return m_ValidOperation;
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
	constexpr ImU32 backgroundColor = 0x10101010;
	constexpr float cameraDistance = 8.0f;

	ImGuizmo::SetDrawlist();
	ImGuizmo::SetRect(m_X, m_Y, m_Width, m_Height);

	auto [viewGizmosPosition, viewGizmosSize] = getViewGizmoRect();

	float *viewMatrix = glm::value_ptr(camera.getViewMatrix());
	ImGuizmo::ViewManipulate(viewMatrix, cameraDistance, viewGizmosPosition, viewGizmosSize, backgroundColor);

	decomposeViewMatrix(camera, camera.getViewMatrix());
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

bool Survive::Gizmos::isInsideViewGizmo()
{
	ImVec2 position = ImGui::GetMousePos();
	auto [rectUpperLeft, rectSize] = getViewGizmoRect();

	return position.x >= rectUpperLeft.x && position.y >= rectUpperLeft.y &&
		   position.x <= rectUpperLeft.x + rectSize.x && position.y <= rectUpperLeft.y + rectSize.y;
}

std::pair<ImVec2, ImVec2> Survive::Gizmos::getViewGizmoRect()
{
	float size = 0.2f * std::min(Scene::getSceneWidth(), Scene::getSceneHeight());
	ImVec2 viewGizmosSize{size, size};

	auto [sceneX, sceneY] = Scene::getScenePosition();
	float padding = Scene::getSceneRegionMin().first;
	ImVec2 viewGizmosPosition{sceneX - padding + Scene::getSceneWidth() - viewGizmosSize.x, sceneY};

	return {viewGizmosPosition, viewGizmosSize};
}
