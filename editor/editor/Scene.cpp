//
// Created by david on 26. 11. 2021..
//

#include <imgui.h>

#include "Scene.h"

float Survive::Scene::m_SceneWidth{};
float Survive::Scene::m_SceneHeight{};
float Survive::Scene::m_ScenePosX{};
float Survive::Scene::m_ScenePosY{};
float Survive::Scene::m_SceneRegionX{};
float Survive::Scene::m_SceneRegionY{};

bool Survive::Scene::m_SceneFocused{};

Survive::Scene::Scene(const Texture &scene)
		: m_Scene(scene)
{

}

void Survive::Scene::renderSceneWindow(Camera &camera, Renderer &renderer, entt::registry &registry,
									   entt::entity selectedEntity, bool isScenePlaying)
{
	if (ImGui::Begin("Scene window"))
	{
		ImVec2 pos = ImGui::GetCursorScreenPos();
		collectSceneData();

		auto textureId = reinterpret_cast<ImTextureID>(m_Scene.textureId());
		ImGui::GetWindowDrawList()->AddImage(textureId, pos,
											 ImVec2(pos.x + m_SceneWidth, pos.y + m_SceneHeight), ImVec2(0, 1),
											 ImVec2(1, 0));

		if (!isScenePlaying)
		{
			m_Gizmos.setRect(pos.x, pos.y, m_SceneWidth, m_SceneHeight);
			m_Gizmos.draw(registry, camera, selectedEntity);
		}

		renderer.renderScene(registry, camera, !isScenePlaying);
	}

	ImGui::End();
}

float Survive::Scene::getSceneWidth()
{
	return m_SceneWidth;
}

float Survive::Scene::getSceneHeight()
{
	return m_SceneHeight;
}

std::pair<float, float> Survive::Scene::getScenePosition()
{
	return {m_ScenePosX, m_ScenePosY};
}

std::pair<float, float> Survive::Scene::getSceneRegionMin()
{
	return {m_SceneRegionX, m_SceneRegionY};
}

bool Survive::Scene::isSceneFocused()
{
	return m_SceneFocused;
}

void Survive::Scene::collectSceneData()
{
	ImVec2 pos = ImGui::GetCursorScreenPos();

	m_ScenePosX = pos.x;
	m_ScenePosY = pos.y;

	m_SceneRegionX = ImGui::GetWindowContentRegionMin().x;
	m_SceneRegionY = ImGui::GetWindowContentRegionMin().y;

	m_SceneWidth = ImGui::GetWindowWidth();
	m_SceneHeight = ImGui::GetWindowHeight();

	m_SceneFocused = !ImGui::IsPopupOpen("", ImGuiPopupFlags_AnyPopupId | ImGuiPopupFlags_AnyPopupLevel);
}

bool Survive::Scene::isInsideScene()
{
	float x = ImGui::GetMousePos().x;
	float y = ImGui::GetMousePos().y;

	return x >= m_ScenePosX && x <= m_ScenePosX + m_SceneWidth &&
		   y >= m_ScenePosY && y <= m_ScenePosY + m_SceneHeight;
}

void Survive::Scene::handleKeyEvents(const EventHandler &eventHandler)
{
	if (m_SceneFocused)
	{
		m_Gizmos.handleKeyEvents(eventHandler);
	}
}