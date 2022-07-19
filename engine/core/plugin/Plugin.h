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

			auto destroyFunction = reinterpret_cast<DestroyFunction>(getFunctionAddress(m_ClassInstance, "destroy"));

			if (destroyFunction == nullptr)
			{
				Log::logMessage(LogType::ERROR, "Error while loading \"destroy()\" function");
			} else
			{
				destroyFunction(object);
			}

			closeInstance(m_ClassInstance);
		}

		ObjectBehaviour *createInstance(const std::string &filename)
		{
			m_ClassInstance = openLibrary(filename);

			if (m_ClassInstance == nullptr)
			{
				Log::logMessage(LogType::ERROR, "Error while loading " + filename);
				return nullptr;
			}

			auto createFunction = reinterpret_cast<CreateFunction>(getFunctionAddress(m_ClassInstance, "create"));

			if (createFunction == nullptr)
			{
				Log::logMessage(LogType::ERROR, "Error while loading \"create()\" function");
				return nullptr;
			}

			ObjectBehaviour *objectBehaviour = createFunction();
			return objectBehaviour;
		}

	private:
		static void closeInstance(void *instance)
		{
#if defined(_WIN32) || defined(_WIN64)
			// TODO implement for windows
#else
			dlclose(instance);
#endif
		}

		static void *getFunctionAddress(void *instance, const char *name)
		{
#if defined(_WIN32) || defined(_WIN64)
			// TODO implement for windows
			return nullptr;
#else
			return dlsym(instance, name);
#endif
		}

		static void *openLibrary(const std::string &filename)
		{
#if defined(_WIN32) || defined(_WIN64)
			// TODO implement for windows
			return nullptr;
#else
			return dlopen(filename.c_str(), RTLD_LAZY);
#endif
		}
	};
}

#endif //SURVIVE_PLUGIN_H
