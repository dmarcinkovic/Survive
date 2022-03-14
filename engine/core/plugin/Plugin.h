//
// Created by david on 05. 03. 2022..
//

#ifndef SURVIVE_PLUGIN_H
#define SURVIVE_PLUGIN_H

#include <memory>
#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
// TODO implement for windows
#else

#include <dlfcn.h>

#endif

#include "ObjectBehaviour.h"

namespace Survive
{
	class Plugin
	{
	private:
		void *m_Instance{};

	public:
		using CreateFunction = ObjectBehaviour *(*)();
		using DestroyFunction = void (*)(ObjectBehaviour *);

		void deleteInstance(const std::shared_ptr<ObjectBehaviour> &instance)
		{
			if (m_Instance == nullptr)
			{
				return;
			}

			auto destroyFunction = reinterpret_cast<DestroyFunction>(dlsym(m_Instance, "destroy"));
			dlclose(m_Instance);

			if (destroyFunction == nullptr)
			{
				Log::logMessage(LogType::ERROR, "Error while loading \"destroy()\" function");
			} else
			{
				destroyFunction(instance.get());
			}
		}

		std::shared_ptr<ObjectBehaviour> createInstance(const std::string &filename)
		{
			m_Instance = dlopen(filename.c_str(), RTLD_LAZY);

			if (m_Instance == nullptr)
			{
				Log::logMessage(LogType::ERROR, "Error while loading " + filename);
				return nullptr;
			}

			auto createFunction = reinterpret_cast<CreateFunction>(dlsym(m_Instance, "create"));

			if (createFunction == nullptr)
			{
				Log::logMessage(LogType::ERROR, "Error while loading \"create()\" function");
				return nullptr;
			}

			ObjectBehaviour *objectBehaviour = createFunction();
			return std::shared_ptr<ObjectBehaviour>{objectBehaviour};
		}
	};
}

#endif //SURVIVE_PLUGIN_H
