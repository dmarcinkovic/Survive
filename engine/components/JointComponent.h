//
// Created by david on 26.04.22..
//

#ifndef SURVIVE_JOINTCOMPONENT_H
#define SURVIVE_JOINTCOMPONENT_H

#include <string>

#include "entt.hpp"

namespace Survive
{
	struct JointComponent
	{
		entt::entity connectedBody = entt::null;
		std::string connectedBodyName = "none";

		JointComponent() = default;

		explicit JointComponent(entt::entity connectedBody)
				: connectedBody(connectedBody)
		{}
	};
}

#endif //SURVIVE_JOINTCOMPONENT_H
