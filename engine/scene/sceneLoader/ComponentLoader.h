//
// Created by david on 03. 07. 2021..
//

#ifndef SURVIVE_COMPONENTLOADER_H
#define SURVIVE_COMPONENTLOADER_H

#include <fstream>

#include "entt.hpp"

namespace Survive
{
	class ComponentLoader
	{
	public:
		static void loadBloomComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadReflectionComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadRefractionComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadRender2DComponent(entt::registry &registry, entt::entity entity,
							  std::ifstream &reader, Loader &loader);

		static void loadRender3DComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader,
										  Loader &loader);

		static void loadRigidBodyComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadShadowComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadTransformComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

	private:
		static std::string parseLine(std::ifstream &reader);

		static glm::vec3 parseVec3(const std::string &vec3);
	};
}

#endif //SURVIVE_COMPONENTLOADER_H
