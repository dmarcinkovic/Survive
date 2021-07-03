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
		static void loadBloomComponent(entt::registry &registry, std::ifstream &reader);

		static void loadReflectionComponent(entt::registry &registry, std::ifstream &reader);

		static void loadRefractionComponent(entt::registry &registry, std::ifstream &reader);

		static void loadRender2DComponent(entt::registry &registry, std::ifstream &reader);

		static void loadRender3DComponent(entt::registry &registry, std::ifstream &reader);

		static void loadRigidBodyComponent(entt::registry &registry, std::ifstream &reader);

		static void loadShadowComponent(entt::registry &registry, std::ifstream &reader);

		static void loadTransformComponent(entt::registry &registry, std::ifstream &reader);
	};
}

#endif //SURVIVE_COMPONENTLOADER_H
