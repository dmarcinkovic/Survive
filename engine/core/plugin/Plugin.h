//
// Created by david on 05. 03. 2022..
//

#ifndef SURVIVE_PLUGIN_H
#define SURVIVE_PLUGIN_H

#include <memory>

#if defined(_WIN32) || defined(_WIN64)
// TODO implement window
#else

#include <dlfcn.h>

#endif

namespace Survive
{
	class Plugin
	{
		template<class T>
		static std::shared_ptr<T> createInstance(const std::string &filename)
		{
			void *instance = dlopen(filename.c_str(), RTLD_LAZY);
			std::shared_ptr<T> object = dlsym(instance, "create");

			return object;
		}

		template<class T>
		static void deleteInstance(const std::shared_ptr<T> &instance)
		{
			dlclose(instance);
		}
	};
}

#endif //SURVIVE_PLUGIN_H
