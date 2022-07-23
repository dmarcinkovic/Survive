//
// Created by david on 23.07.22..
//

#if defined(_WIN32) || defined(_WIN64)
// TODO implement for windows
#else
#include <dlfcn.h>
#endif

#include "Plugin.h"

void Survive::Plugin::closeInstance(void *instance)
{
#if defined(_WIN32) || defined(_WIN64)
	// TODO implement for windows
#else
	dlclose(instance);
#endif
}

void *Survive::Plugin::getFunctionAddress(void *instance, const char *name)
{
#if defined(_WIN32) || defined(_WIN64)
	// TODO implement for windows
			return nullptr;
#else
	return dlsym(instance, name);
#endif
}

void *Survive::Plugin::openLibrary(const std::string &filename)
{
#if defined(_WIN32) || defined(_WIN64)
	// TODO implement for windows
			return nullptr;
#else
	return dlopen(filename.c_str(), RTLD_LAZY);
#endif
}