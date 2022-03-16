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
		void *m_ClassInstance{};

	public:
		using CreateFunction = ObjectBehaviour *(*)();
		using DestroyFunction = void (*)(ObjectBehaviour *);

		void deleteInstance(ObjectBehaviour *object)
		{
			if (m_ClassInstance == nullptr)
			{
				return;
			}

			auto destroyFunction = reinterpret_cast<DestroyFunction>(dlsym(m_ClassInstance, "destroy"));

			if (destroyFunction == nullptr)
			{
				Log::logMessage(LogType::ERROR, "Error while loading \"destroy()\" function");
			} else
			{
				destroyFunction(object);
			}

			dlclose(m_ClassInstance);
		}

		ObjectBehaviour *createInstance(const std::string &filename)
		{
			m_ClassInstance = dlopen(filename.c_str(), RTLD_LAZY);

			if (m_ClassInstance == nullptr)
			{
				Log::logMessage(LogType::ERROR, "Error while loading " + filename);
				return nullptr;
			}

			auto createFunction = reinterpret_cast<CreateFunction>(dlsym(m_ClassInstance, "create"));

			if (createFunction == nullptr)
			{
				Log::logMessage(LogType::ERROR, "Error while loading \"create()\" function");
				return nullptr;
			}

			ObjectBehaviour *objectBehaviour = createFunction();
			return objectBehaviour;
		}
	};
}

#endif //SURVIVE_PLUGIN_H
