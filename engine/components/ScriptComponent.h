//
// Created by david on 24. 02. 2022..
//

#ifndef SURVIVE_SCRIPTCOMPONENT_H
#define SURVIVE_SCRIPTCOMPONENT_H

#include <memory>

#include "ObjectBehaviour.h"

namespace Survive
{
	struct ScriptComponent
	{
		std::unique_ptr<ObjectBehaviour> script;

		ScriptComponent() = default;

		explicit ScriptComponent(std::unique_ptr<ObjectBehaviour> objectBehaviour)
			: script(std::move(objectBehaviour))
		{
		}
	};
}

#endif //SURVIVE_SCRIPTCOMPONENT_H
