//
// Created by david on 03. 07. 2021..
//

#ifndef SURVIVE_COMPONENTLOADER_H
#define SURVIVE_COMPONENTLOADER_H

#include <fstream>
#include <optional>

#include "entt.hpp"
#include "Font.h"
#include "AudioMaster.h"

namespace Survive
{
	class ComponentLoader
	{
	public:
		static void loadAnimationComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadBloomComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader, Loader &loader);

		static void loadReflectionComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadRefractionComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadRender2DComponent(entt::registry &registry, entt::entity entity,
										  std::ifstream &reader, Loader &loader);

		static void loadRender3DComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader,
										  Loader &loader);

		static void loadRigidBodyComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadShadowComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadSoundComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader,
									   AudioMaster &audioMaster);

		static void loadSpriteComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadSpriteSheetComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadTransformComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void
		loadTextComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader, Loader &loader);

	private:
		static std::string parseLine(std::ifstream &reader, const char *text);

		static glm::vec3 parseVec3(const std::string &vec3);

		static glm::vec4 parseVec4(const std::string &vec4);

		static std::optional<Font> getFont(const std::string &fontFile, const std::string &textureAtlas, Loader &loader);
	};
}

#endif //SURVIVE_COMPONENTLOADER_H
