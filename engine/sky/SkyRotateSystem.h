//
// Created by david on 29. 03. 2021..
//

#ifndef SURVIVE_SKYROTATESYSTEM_H
#define SURVIVE_SKYROTATESYSTEM_H

#include "../../ecs/entt.hpp"

namespace Survive
{
	class SkyRotateSystem
	{
	public:
		static void rotateSky(entt::registry &registry, entt::entity sky);
	};
}

#endif //SURVIVE_SKYROTATESYSTEM_H
