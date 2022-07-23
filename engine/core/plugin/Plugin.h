//
// Created by david on 05. 03. 2022..
//

#ifndef SURVIVE_PLUGIN_H
#define SURVIVE_PLUGIN_H

#include <memory>

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
				Log::logMessage(LogType::Error, "Error while loading \"destroy()\" function");
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
				Log::logMessage(LogType::Error, "Error while loading " + filename);
				return nullptr;
			}

			auto createFunction = reinterpret_cast<CreateFunction>(getFunctionAddress(m_ClassInstance, "create"));

			if (createFunction == nullptr)
			{
				Log::logMessage(LogType::Error, "Error while loading \"create()\" function");
				return nullptr;
			}

			ObjectBehaviour *objectBehaviour = createFunction();
			return objectBehaviour;
		}

	private:
		static void closeInstance(void *instance);

		static void *getFunctionAddress(void *instance, const char *name);

		static void *openLibrary(const std::string &filename);
	};
}

#endif //SURVIVE_PLUGIN_H
