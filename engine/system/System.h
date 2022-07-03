//
// Created by david on 22. 11. 2021..
//

#ifndef SURVIVE_SYSTEM_H
#define SURVIVE_SYSTEM_H

#include <box2d/box2d.h>
#include <entt.hpp>

#include "EventHandler.h"

namespace Survive
{
	class System
	{
	public:
		static void update(entt::registry &registry, b2World *world2D, rp3d::PhysicsWorld *world3D);

		static void init(entt::registry &registry, EventHandler &eventHandler, b2World *world2D,
						 rp3d::PhysicsWorld *world3D, rp3d::PhysicsCommon &physicsCommon, Camera &camera);

		static void destroy(entt::registry &registry);
	};
}

#endif //SURVIVE_SYSTEM_H
