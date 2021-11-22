//
// Created by david on 22. 11. 2021..
//

#ifndef SURVIVE_SYSTEM_H
#define SURVIVE_SYSTEM_H

#include "entt.hpp"

namespace Survive
{
	class System
	{
	public:
		void update(entt::registry &registry);
	};
}

#endif //SURVIVE_SYSTEM_H
