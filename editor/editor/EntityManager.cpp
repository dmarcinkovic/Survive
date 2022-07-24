//
// Created by david on 08. 05. 2021..
//

#include <imgui.h>

#include "ComponentUtil.h"
#include "EntityManager.h"
#include "RegistryUtil.h"

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
		registry.emplace<OutlineComponent>(entity, false);
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

			drawSelectable(registry, tag, entity, index);
			drawPopupContext(registry, entity, index);
		}
	});

	ImGui::PopStyleColor(3);
}

void Survive::EntityManager::drawPropertyPanel(entt::registry &registry)
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));

	if (!registry.valid(m_SelectedEntity))
	{
		resetEntity();
	}

	if (m_AddNewComponent && m_SelectedEntity != entt::null)
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
	setStyleColors();
	m_Util.drawAllComponents(registry, m_SelectedEntity);
	resetStyleColors();
}

void Survive::EntityManager::addNewComponent(entt::registry &registry)
{
	static std::vector<const char *> m_Components = ComponentUtil::getListOfComponents();
	static int size = static_cast<int>(m_Components.size());

	setStyleColors();
	ImGui::Combo("Component type", &m_CurrentItem, m_Components.data(), size);

	if (m_CurrentItem >= 0)
	{
		bool componentAdded = m_Util.addComponent(registry, m_SelectedEntity, m_CurrentItem);
		if (componentAdded)
		{
			m_CurrentItem = -1;
		}
	}

	resetStyleColors();
}

void Survive::EntityManager::drawSelectable(entt::registry &registry, const TagComponent &tag,
											entt::entity selectedEntity, int i)
{
	ImGui::PushID(i);
	if (ImGui::Selectable(tag.tag.c_str(), m_Selected == i))
	{
		drawOutline(registry, m_SelectedEntity, false);

		m_SelectedEntity = selectedEntity;
		m_AddNewComponent = false;
		m_Selected = i;
		m_CurrentItem = -1;

		drawOutline(registry, m_SelectedEntity, true);
	}

	initializeDragDropSource(selectedEntity, tag);

	ImGui::PopID();
}

void Survive::EntityManager::drawPopupContext(entt::registry &registry, entt::entity selectedEntity, int i)
{
	if (ImGui::BeginPopupContextItem())
	{
		m_AddNewComponent = ImGui::Selectable("Add new component");

		if (m_AddNewComponent)
		{
			drawOutline(registry, m_SelectedEntity, false);
			m_CurrentItem = -1;
			m_Selected = i;
			m_SelectedEntity = selectedEntity;
			drawOutline(registry, m_SelectedEntity, true);
		} else if (ImGui::Selectable("Remove entity"))
		{
			drawOutline(registry, m_SelectedEntity, false);

			m_Selected = i;
			m_SelectedEntity = selectedEntity;
			removeEntity(registry);
		} else if (ImGui::Selectable("Rename entity"))
		{
			drawOutline(registry, m_SelectedEntity, false);
			m_Selected = i;
			m_SelectedEntity = selectedEntity;
			m_RenameEntity = true;
			drawOutline(registry, m_SelectedEntity, true);
		} else if (ImGui::Selectable("Copy entity"))
		{
			copyEntity(registry, selectedEntity, i);
		}

		ImGui::EndPopup();
	}
}

void Survive::EntityManager::removeEntity(entt::registry &registry)
{
	registry.destroy(m_SelectedEntity);
	resetEntity();
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
	if (eventHandler.isKeyPressed(Key::DELETE_KEY) && m_Selected != -1)
	{
		m_DestroyEntity = true;
	}
}

entt::entity Survive::EntityManager::getSelectedEntity() const
{
	return m_SelectedEntity;
}

void Survive::EntityManager::setSelectedEntity(entt::registry &registry, int selectedEntity)
{
	if (selectedEntity == -2)
	{
		return;
	}

	drawOutline(registry, m_SelectedEntity, false);

	m_SelectedEntity = selectedEntity == -1 ? entt::null : entt::entity(selectedEntity);
	m_Selected = selectedEntity;

	if (m_SelectedEntity != entt::null)
	{
		drawOutline(registry, m_SelectedEntity, true);
	}
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

void Survive::EntityManager::initializeDragDropSource(entt::entity selectedEntity, const TagComponent &tag)
{
	if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
	{
		auto id = static_cast<int>(selectedEntity);
		const char *data = tag.tag.c_str();

		std::tuple<int, int, const char *> payload = std::make_tuple(m_Selected, id, data);

		ImGui::SetDragDropPayload("Entity", &payload, sizeof(payload));
		ImGui::EndDragDropSource();
	}
}

void Survive::EntityManager::resetEntity()
{
	m_SelectedEntity = entt::null;
	m_Selected = m_CurrentItem = -1;
}

void Survive::EntityManager::setStyleColors()
{
	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.4f, 0.4f, 0.35f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.4f, 0.4f, 0.5f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.25f, 0.25f, 0.3f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.3f, 0.3f, 0.35f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
}

void Survive::EntityManager::resetStyleColors()
{
	ImGui::PopStyleColor(7);
}

void Survive::EntityManager::drawOutline(entt::registry &registry, entt::entity entity, bool draw)
{
	if (!draw && entity == entt::null)
	{
		return;
	}

	if (registry.any_of<OutlineComponent>(entity))
	{
		OutlineComponent &outline = registry.get<OutlineComponent>(entity);
		outline.drawOutline = draw;
	}
}

void Survive::EntityManager::copyEntity(entt::registry &registry, entt::entity selectedEntity, int i)
{
	drawOutline(registry, m_SelectedEntity, false);

	entt::entity copy = registry.create();
	m_Selected = i;
	m_SelectedEntity = selectedEntity;
	RegistryUtil::copyEntity(registry, m_SelectedEntity, copy);

	TagComponent &tag = registry.get<TagComponent>(copy);
	tag.tag += "_2";

	drawOutline(registry, m_SelectedEntity, true);
}
