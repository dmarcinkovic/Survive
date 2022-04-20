//
// Created by david on 03. 07. 2021..
//

#ifndef SURVIVE_COMPONENTLOADER_H
#define SURVIVE_COMPONENTLOADER_H

#include <fstream>
#include <optional>
#include <box2d/box2d.h>
#include <tuple>

#include "entt.hpp"
#include "Font.h"
#include "AudioMaster.h"

namespace Survive
{
	class ComponentLoader
	{
	public:
		static void loadAnimationComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void
		loadBloomComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader, Loader &loader);

		static void loadReflectionComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadRefractionComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadRender2DComponent(entt::registry &registry, entt::entity entity,
										  std::ifstream &reader, Loader &loader);

		static void loadRender3DComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader,
										  Loader &loader);

		static void loadMaterialComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader,
										  Loader &loader);

		static void loadShadowComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadSoundComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader,
									   AudioMaster &audioMaster);

		static void loadSpriteComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadSpriteSheetComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadTransformComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void
		loadTextComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader, Loader &loader);

		static void loadBox2DColliderComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadCircleCollider2DComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void
		loadPolygonCollider2DComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadEdgeCollider2DComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadHingeJoint2DComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadDistanceJoint2DComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadRigidBody2DComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadOutlineComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

	private:
		static std::string parseLine(std::ifstream &reader, const char *text);

		static glm::vec3 parseVec3(const std::string &vec3);

		static glm::vec4 parseVec4(const std::string &vec4);

		static b2Vec2 parseVec2(const std::string &vec2);

		static std::optional<Font>
		getFont(const std::string &fontFile, const std::string &textureAtlas, Loader &loader);

		static std::tuple<float, float, float> loadCollider2DComponent(std::ifstream &reader);
	};
}

#endif //SURVIVE_COMPONENTLOADER_H
