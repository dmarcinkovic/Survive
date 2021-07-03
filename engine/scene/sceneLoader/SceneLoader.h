//
// Created by david on 23. 06. 2021..
//

#ifndef SURVIVE_SCENELOADER_H
#define SURVIVE_SCENELOADER_H

#include "entt.hpp"
#include "Components.h"

class SceneLoader
{
public:
	static void loadScene(entt::registry &registry, const std::string &filename);

private:
//	static void loadEntity
};


#endif //SURVIVE_SCENELOADER_H
