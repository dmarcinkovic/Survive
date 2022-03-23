//
// Created by david on 24. 02. 2022..
//

#ifndef SURVIVE_SCRIPTCOMPONENT_H
#define SURVIVE_SCRIPTCOMPONENT_H

#include <memory>

#include "ObjectBehaviour.h"
#include "Plugin.h"

namespace Survive
{
	struct ScriptComponent
	{
		friend class ScriptingSystem;

		template<typename ComponentType> friend
		class ComponentTemplate;

	public:
		std::string pluginLocation;
		ObjectBehaviour *script{};

	private:
		Plugin m_Plugin;

	public:
		ScriptComponent() = default;

		explicit ScriptComponent(ObjectBehaviour *objectBehaviour)
				: script(objectBehaviour)
		{
		}
	};
}

#endif //SURVIVE_SCRIPTCOMPONENT_H
