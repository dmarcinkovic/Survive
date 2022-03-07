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

namespace Survive
{
	class Plugin
	{
	public:
		using Function = ObjectBehaviour *(*)();

		static void deleteInstance(const std::shared_ptr<ObjectBehaviour> &instance)
		{
//			dlclose(instance);
		}

		static std::shared_ptr<ObjectBehaviour> createInstance(const std::string &filename)
		{
			void *instance = dlopen(filename.c_str(), RTLD_LAZY);

			if (instance == nullptr)
			{
				std::cout << "Error: " << dlerror() << '\n';
				Log::logMessage(LogType::ERROR, "Error while loading " + filename);
				return nullptr;
			}

			auto createFunction = reinterpret_cast<Function>(dlsym(instance, "create"));

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
