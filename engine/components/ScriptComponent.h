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

	public:
		std::shared_ptr<ObjectBehaviour> script;

	private:
		Plugin m_Plugin;

		std::string m_PluginLocation;

	public:
		ScriptComponent() = default;

		explicit ScriptComponent(std::shared_ptr<ObjectBehaviour> objectBehaviour)
				: script(std::move(objectBehaviour))
		{
		}
	};
}

#endif //SURVIVE_SCRIPTCOMPONENT_H
