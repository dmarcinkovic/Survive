//
// Created by david on 23. 06. 2021..
//

#ifndef SURVIVE_SCENELOADER_H
#define SURVIVE_SCENELOADER_H

#include <fstream>

#include "entt.hpp"
#include "Components.h"

class SceneLoader
{
public:
	static void loadScene(entt::registry &registry, const std::string &filename);

private:
	static void loadEntity(entt::registry &registry, std::ifstream &reader);

	static void loadComponent(entt::registry &registry, std::ifstream &reader, const std::string &component);
};


#endif //SURVIVE_SCENELOADER_H
