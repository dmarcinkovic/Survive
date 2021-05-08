//
// Created by david on 08. 05. 2021..
//

#include <imgui.h>

#include "ComponentType.h"
#include "EntityManager.h"

void Survive::EntityManager::addEntity(entt::registry &registry)
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
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
	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.1f, 0.2f, 0.3f, 1.0f));
	if (ImGui::InputText("Entity name", m_Buffer, BUFFER_SIZE,
						 ImGuiInputTextFlags_CtrlEnterForNewLine | ImGuiInputTextFlags_EnterReturnsTrue))
	{
		auto entity = registry.create();
		registry.emplace<TagComponent>(entity, m_Buffer);
		m_Selected = -1;

		memset(m_Buffer, 0, BUFFER_SIZE);
		ImGui::CloseCurrentPopup();
	}

	ImGui::PopStyleColor();
}

void Survive::EntityManager::listEntities(entt::registry &registry)
{
	ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.0f, 0.2f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.35f, 0.5f, 0.5f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.1f, 0.3f, 0.3f, 1.0f));

	auto entities = registry.data();
	for (int i = 0; i < registry.size(); ++i)
	{
		const TagComponent &tag = registry.get<TagComponent>(entities[i]);

		if (ImGui::Selectable(tag.tag.c_str(), m_Selected == i))
		{
			m_SelectedEntity = entities[i];
			m_AddNewComponent = false;
			m_Selected = i;
		}

		if (ImGui::BeginPopupContextItem())
		{
			m_AddNewComponent = ImGui::Selectable("Add new component");

			if (m_AddNewComponent)
			{
				m_Selected = -1;
			}

			ImGui::EndPopup();
		}
	}

	ImGui::PopStyleColor(3);
}

void Survive::EntityManager::drawPropertyPanel(entt::registry &registry)
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));

	if (m_AddNewComponent)
	{
		addNewComponent();
	} else if (m_Selected >= 0)
	{
		listComponents(registry);
	}

	ImGui::PopStyleColor();
}

void Survive::EntityManager::listComponents(entt::registry &registry)
{
	drawTag(registry.get<TagComponent>(m_SelectedEntity));
	ImGui::SameLine();

	if (ImGui::Button("Add component"))
	{
		m_AddNewComponent = true;
	}
}

void Survive::EntityManager::drawTag(const TagComponent &tag)
{
	char *buffer = const_cast<char *>(tag.tag.c_str());

	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.2f, 0.2f, 1.0f));
	ImGui::InputText("", buffer, tag.tag.capacity(), ImGuiInputTextFlags_ReadOnly);
	ImGui::PopStyleColor();
}

void Survive::EntityManager::addNewComponent()
{
	static std::vector<const char *> m_Components = ComponentList::getListOfComponents();
	static int size = static_cast<int>(m_Components.size());

	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.2f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.1f, 0.3f, 0.3f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.1f, 0.4f, 0.35f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.1f, 0.2f, 0.2f, 1.0f));

	ImGui::Combo("Component type", &m_CurrentItem, m_Components.data(), size);
	ImGui::PopStyleColor(4);
}
