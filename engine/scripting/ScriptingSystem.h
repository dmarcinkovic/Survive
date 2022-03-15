//
// Created by david on 26. 02. 2022..
//

#ifndef SURVIVE_SCRIPTINGSYSTEM_H
#define SURVIVE_SCRIPTINGSYSTEM_H

#include "entt.hpp"
#include "EventHandler.h"

namespace Survive
{
	class ScriptingSystem
	{
	public:
		static void init(entt::registry &registry, EventHandler &eventHandler);

		static void update(entt::registry &registry);

		static void destroy(entt::registry &registry);

	private:
		static void initializeScriptingEntity(std::shared_ptr<ObjectBehaviour> &script, entt::registry &registry,
											  entt::entity entity, EventHandler &eventHandler);
	};
}

#endif //SURVIVE_SCRIPTINGSYSTEM_H
