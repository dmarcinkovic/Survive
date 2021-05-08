//
// Created by david on 08. 05. 2021..
//

#include <imgui.h>

#include "TagComponent.h"
#include "EntityManager.h"

void Survive::EntityManager::addEntity(entt::registry &registry)
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
	if (ImGui::Button("Create new entity"))
	{
		ImGui::OpenPopup("Create entity");
	}

	if (ImGui::BeginPopup("Create entity"))
	{
		createEntity(registry);
		ImGui::EndPopup();
	}

	ImGui::Separator();

	listEntities(registry);

	ImGui::PopStyleColor();
}

void Survive::EntityManager::createEntity(entt::registry &registry)
{
	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(1.0f, 0.2, 0.2, 1.0f));
	if (ImGui::InputText("Entity name", buffer, BUFFER_SIZE,
						 ImGuiInputTextFlags_CtrlEnterForNewLine | ImGuiInputTextFlags_EnterReturnsTrue))
	{
		auto entity = registry.create();
		registry.emplace<TagComponent>(entity, buffer);

		memset(buffer, 0, BUFFER_SIZE);
		ImGui::CloseCurrentPopup();
	}

	ImGui::PopStyleColor();
}

void Survive::EntityManager::listEntities(entt::registry &registry)
{
	ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.0f,0.2f,0.2f,1.0f));
	ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.35f,0.5f,0.5f,1.0f));
	ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.1f, 0.3f, 0.3f, 1.0f));

	registry.each([&](const entt::entity entity){
		const TagComponent &tag = registry.get<TagComponent>(entity);

		ImGui::CollapsingHeader(tag.tag.c_str());
	});

	ImGui::PopStyleColor(3);
}
