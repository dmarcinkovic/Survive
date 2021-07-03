//
// Created by david on 23. 06. 2021..
//

#ifndef SURVIVE_SCENELOADER_H
#define SURVIVE_SCENELOADER_H

#include <fstream>

#include "entt.hpp"
#include "Components.h"

namespace Survive
{
	class SceneLoader
	{
	public:
		static void loadScene(entt::registry &registry, const std::string &filename);

	private:
		static void loadEntity(entt::registry &registry, std::ifstream &reader, const std::string &tag);

		static void loadComponent(entt::registry &registry, std::ifstream &reader, const std::string &component);

		static entt::entity createEntity(entt::registry &registry, const std::string &tag);
	};
}

#endif //SURVIVE_SCENELOADER_H
