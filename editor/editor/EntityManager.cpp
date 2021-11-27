//
// Created by david on 08. 05. 2021..
//

#include <imgui.h>

#include "ComponentUtil.h"
#include "EntityManager.h"
#include "EditorUtil.h"

bool Survive::EntityManager::addEntity(entt::registry &registry)
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
	if (ImGui::Button("Create new entity"))
	{
		ImGui::OpenPopup("Create entity");
	}

	if ((m_CreateOpen = ImGui::BeginPopup("Create entity")))
	{
		createEntity(registry);
		ImGui::EndPopup();
	}

	ImGui::Separator();

	listEntities(registry);
	renameEntity(registry);

	if (m_DestroyEntity)
	{
		m_DestroyEntity = false;
		removeEntity(registry);
	}

	ImGui::PopStyleColor();

	return m_AddNewComponent || m_Selected >= 0;
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

	registry.each([&](const entt::entity entity) {
		if (registry.any_of<TagComponent>(entity))
		{
			const TagComponent &tag = registry.get<TagComponent>(entity);
			auto index = static_cast<int>(entity);

			drawSelectable(tag, entity, index);
			drawPopupContext(registry, entity, index);
		}
	});

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
	EditorUtil::setStyleColors();
	m_Util.drawAllComponents(registry, m_SelectedEntity);
	EditorUtil::resetStyleColors();
}

void Survive::EntityManager::addNewComponent(entt::registry &registry)
{
	static std::vector<const char *> m_Components = ComponentUtil::getListOfComponents();
	static int size = static_cast<int>(m_Components.size());

	EditorUtil::setStyleColors();
	ImGui::Combo("Component type", &m_CurrentItem, m_Components.data(), size);

	if (m_CurrentItem >= 0)
	{
		bool componentAdded = m_Util.addComponent(registry, m_SelectedEntity, m_CurrentItem);
		if (componentAdded)
		{
			m_CurrentItem = -1;
		}
	}

	EditorUtil::resetStyleColors();
}

void Survive::EntityManager::drawSelectable(const Survive::TagComponent &tag, entt::entity selectedEntity, int i)
{
	ImGui::PushID(i);
	if (ImGui::Selectable(tag.tag.c_str(), m_Selected == i))
	{
		m_SelectedEntity = selectedEntity;
		m_AddNewComponent = false;
		m_Selected = i;
		m_CurrentItem = -1;
	}
	ImGui::PopID();
}

void Survive::EntityManager::drawPopupContext(entt::registry &registry, entt::entity selectedEntity, int i)
{
	if (ImGui::BeginPopupContextItem())
	{
		m_AddNewComponent = ImGui::Selectable("Add new component");

		if (m_AddNewComponent)
		{
			m_CurrentItem = -1;
			m_Selected = i;
			m_SelectedEntity = selectedEntity;
		} else if (ImGui::Selectable("Remove entity"))
		{
			m_Selected = i;
			m_SelectedEntity = selectedEntity;
			removeEntity(registry);
		} else if (ImGui::Selectable("Rename entity"))
		{
			m_Selected = i;
			m_SelectedEntity = selectedEntity;
			m_RenameEntity = true;
		}

		ImGui::EndPopup();
	}
}

void Survive::EntityManager::removeEntity(entt::registry &registry)
{
	registry.destroy(m_SelectedEntity);
	m_SelectedEntity = entt::null;

	m_Selected = m_CurrentItem = -1;
}

void Survive::EntityManager::renameEntity(entt::registry &registry)
{
	if (m_RenameEntity)
	{
		ImGui::OpenPopup("rename entity");
		m_RenameEntity = false;
	}

	if ((m_RenameOpen = ImGui::BeginPopup("rename entity")))
	{
		if (ImGui::InputText("Entity name", m_Buffer, BUFFER_SIZE,
							 ImGuiInputTextFlags_CtrlEnterForNewLine | ImGuiInputTextFlags_EnterReturnsTrue))
		{
			registry.replace<TagComponent>(m_SelectedEntity, m_Buffer);
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}

void Survive::EntityManager::handleKeyEvents(const EventHandler &eventHandler)
{
	if (eventHandler.isKeyPressed(Key::DELETE) && m_Selected != -1)
	{
		m_DestroyEntity = true;
	}
}

entt::entity Survive::EntityManager::getSelectedEntity() const
{
	return m_SelectedEntity;
}

void Survive::EntityManager::setSelectedEntity(int selectedEntity)
{
	if (selectedEntity == -2)
	{
		return;
	}

	m_SelectedEntity = selectedEntity == -1 ? entt::null : entt::entity(selectedEntity);
	m_Selected = selectedEntity;
}

bool Survive::EntityManager::isFocused() const
{
	return m_CreateOpen || m_RenameOpen || m_Util.isUsingKeyEvents();
}

void Survive::EntityManager::stopDrawing()
{
	m_AddNewComponent = false;
	m_Selected = -1;
}
