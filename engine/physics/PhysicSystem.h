//
// Created by david on 13. 10. 2021..
//

#ifndef SURVIVE_PHYSICSYSTEM_H
#define SURVIVE_PHYSICSYSTEM_H

#include "entt.hpp"

namespace Survive
{
	class PhysicSystem
	{
	public:
		static void update(entt::registry &registry);
	};
}

#endif //SURVIVE_PHYSICSYSTEM_H
