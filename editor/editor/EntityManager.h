//
// Created by david on 08. 05. 2021..
//

#ifndef SURVIVE_ENTITYMANAGER_H
#define SURVIVE_ENTITYMANAGER_H

#include "entt.hpp"
#include "EventHandler.h"
#include "Components.h"
#include "ComponentUtil.h"

namespace Survive
{
	class EntityManager
	{
	private:
		static constexpr int BUFFER_SIZE = 256;

		char m_Buffer[BUFFER_SIZE]{};
		bool m_AddNewComponent{};

		entt::entity m_SelectedEntity{};
		int m_Selected = -1;
		int m_CurrentItem = -1;
		bool m_RenameEntity{};

		ComponentUtil m_Util{};
		bool m_DestroyEntity{};

	public:
		void addEntity(entt::registry &registry);

		void drawPropertyPanel(entt::registry &registry);

		void handleKeyEvents(const EventHandler &eventHandler);

	private:
		void createEntity(entt::registry &registry);

		void listEntities(entt::registry &registry);

		void listComponents(entt::registry &registry);

		void addNewComponent(entt::registry &registry);

		inline void drawSelectable(const TagComponent &tag, entt::entity selectedEntity, int i);

		inline void drawPopupContext(entt::registry &registry, int i);

		void removeEntity(entt::registry &registry);

		void renameEntity(entt::registry &registry);
	};
}

#endif //SURVIVE_ENTITYMANAGER_H
