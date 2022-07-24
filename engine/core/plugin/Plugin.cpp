//
// Created by david on 23.07.22..
//

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include "Plugin.h"

void Survive::Plugin::closeInstance(void *instance)
{
#if defined(_WIN32) || defined(_WIN64)
	FreeLibrary((HINSTANCE) instance);
#else
	dlclose(instance);
#endif
}

void *Survive::Plugin::getFunctionAddress(void *instance, const char *name)
{
#if defined(_WIN32) || defined(_WIN64)
	return (void *) GetProcAddress((HMODULE) instance, name);
#else
	return dlsym(instance, name);
#endif
}

void *Survive::Plugin::openLibrary(const std::string &filename)
{
#if defined(_WIN32) || defined(_WIN64)
	HMODULE instance = LoadLibraryA(filename.c_str());
	return instance;
#else
	return dlopen(filename.c_str(), RTLD_LAZY);
#endif
}