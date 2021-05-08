//
// Created by david on 08. 05. 2021..
//

#ifndef SURVIVE_ENTITYMANAGER_H
#define SURVIVE_ENTITYMANAGER_H

#include "entt.hpp"

namespace Survive
{
	class EntityManager
	{
	private:
		static constexpr int BUFFER_SIZE = 256;

		char m_Buffer[BUFFER_SIZE]{};

	public:
		void addEntity(entt::registry &registry);

	private:
		void createEntity(entt::registry &registry);

		static void listEntities(entt::registry &registry);
	};
}

#endif //SURVIVE_ENTITYMANAGER_H
