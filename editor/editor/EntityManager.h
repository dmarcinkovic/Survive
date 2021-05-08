//
// Created by david on 08. 05. 2021..
//

#ifndef SURVIVE_ENTITYMANAGER_H
#define SURVIVE_ENTITYMANAGER_H

#include "entt.hpp"
#include "TagComponent.h"

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

	public:
		void addEntity(entt::registry &registry);

		void drawPropertyPanel(entt::registry &registry);

	private:
		void createEntity(entt::registry &registry);

		void listEntities(entt::registry &registry);

		void listComponents(entt::registry &registry);

		static void drawTag(const TagComponent &tag);

		void addNewComponent();
	};
}

#endif //SURVIVE_ENTITYMANAGER_H
