//
// Created by david on 08. 05. 2021..
//

#include <imgui.h>

#include "ComponentUtil.h"
#include "EntityManager.h"
#include "EditorUtil.h"

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

		drawSelectable(tag, entities[i], i);
		drawPopupContext(i);
	}

	ImGui::PopStyleColor(3);
}

void Survive::EntityManager::drawPropertyPanel(entt::registry &registry)
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));

	if (m_AddNewComponent)
	{
		addNewComponent(registry);
	} else if (m_Selected >= 0)
	{
		listComponents(registry);
	}

	ImGui::PopStyleColor();
}

void Survive::EntityManager::listComponents(entt::registry &registry)
{
	// TODO do not forget to change color of collapsing header: It is blue
	ComponentUtil::drawAllComponents(registry, m_SelectedEntity);
}

void Survive::EntityManager::addNewComponent(entt::registry &registry)
{
	static std::vector<const char *> m_Components = ComponentUtil::getListOfComponents();
	static int size = static_cast<int>(m_Components.size());

	EditorUtil::setStyleColors();
	ImGui::Combo("Component type", &m_CurrentItem, m_Components.data(), size);

	if (m_CurrentItem >= 0)
	{
		ComponentUtil::addComponent(registry, m_SelectedEntity, m_CurrentItem);
		ImGui::Columns();

		float width = ImGui::GetColumnWidth() / 2.0f;
		float height = 2.0f * ImGui::GetFontSize();
		if (ImGui::Button("Add component", ImVec2(width, height)))
		{
		}
	}

	ImGui::PopStyleColor(5);
}

void Survive::EntityManager::drawSelectable(const Survive::TagComponent &tag, entt::entity selectedEntity, int i)
{
	if (ImGui::Selectable(tag.tag.c_str(), m_Selected == i))
	{
		m_SelectedEntity = selectedEntity;
		m_AddNewComponent = false;
		m_Selected = i;
		m_CurrentItem = -1;
	}
}

void Survive::EntityManager::drawPopupContext(int i)
{
	if (ImGui::BeginPopupContextItem())
	{
		m_AddNewComponent = ImGui::Selectable("Add new component");

		if (m_AddNewComponent)
		{
			m_CurrentItem = -1;
			m_Selected = i;
		}

		ImGui::EndPopup();
	}
}
