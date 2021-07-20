//
// Created by david on 23. 06. 2021..
//

#ifndef SURVIVE_SCENESERIALIZER_H
#define SURVIVE_SCENESERIALIZER_H

#include <fstream>

#include "entt.hpp"
#include "Components.h"

namespace Survive
{
	class SceneSerializer
	{
	private:
		Loader m_Loader;

	public:
		void loadScene(entt::registry &registry, const std::string &filename);

		static void saveScene(entt::registry &registry, const std::string &filename);

	private:
		void loadEntity(entt::registry &registry, std::ifstream &reader, const std::string &tag);

		void loadComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader,
								  const std::string &component);

		static entt::entity createEntity(entt::registry &registry, const std::string &tag);

		static void saveComponents(entt::registry &registry, entt::entity entity, std::ofstream &writer);
	};
}

#endif //SURVIVE_SCENESERIALIZER_H
