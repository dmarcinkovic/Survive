//
// Created by david on 22. 11. 2021..
//

#ifndef SURVIVE_SYSTEM_H
#define SURVIVE_SYSTEM_H

#include <box2d/box2d.h>

#include "entt.hpp"

namespace Survive
{
	class System
	{
	public:
		static void init(entt::registry &registry, EventHandler &eventHandler, b2World *world, Camera &camera);

		static void update(entt::registry &registry, b2World *world);

		static void destroy(entt::registry &registry);
	};
}

#endif //SURVIVE_SYSTEM_H
