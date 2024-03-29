//
// Created by david on 03. 07. 2021..
//

#ifndef SURVIVE_COMPONENTLOADER_H
#define SURVIVE_COMPONENTLOADER_H

#include <fstream>
#include <optional>
#include <box2d/box2d.h>
#include <tuple>
#include <reactphysics3d/reactphysics3d.h>
#include <entt.hpp>

#include "Font.h"
#include "AudioMaster.h"
#include "TexturedModel.h"

namespace Survive
{
	class ComponentLoader
	{
	public:
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

		static void loadRigidBody3DComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadBoxCollider3DComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadSphereCollider3DComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void
		loadCapsuleCollider3DComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void
		loadConvexMeshCollider3DComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadHingeJoint3DComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadCharacterJoint3DComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadFixedJoint3DComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadOutlineComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader);

		static void loadParticleComponent(entt::registry &registry, entt::entity entity,
										  std::ifstream &reader, Loader &loader);

		static void loadTerrainComponent(entt::registry &registry, entt::entity entity,
										 std::ifstream &reader, Loader &loader);

		static void loadSkyboxComponent(entt::registry &registry, entt::entity entity,
										std::ifstream &reader, Loader &loader);

	private:
		static std::string parseLine(std::ifstream &reader, const char *text);

		static glm::vec3 parseVec3(const std::string &vec3);

		static rp3d::Vector3 parseVector3(const std::string &vec3);

		static glm::vec4 parseVec4(const std::string &vec4);

		static b2Vec2 parseVec2(const std::string &vec2);

		static std::optional<Font>
		getFont(const std::string &fontFile, const std::string &textureAtlas, Loader &loader);

		static std::tuple<float, float, float> loadCollider2DComponent(std::ifstream &reader);

		static std::pair<float, float> loadCollider3DComponent(std::ifstream &reader);

		static bool loadConvexMeshIndices(std::ifstream &reader, std::vector<int> &indices);

		static bool loadConvexMeshVertices(std::ifstream &reader, std::vector<float> &vertices);

		static std::tuple<std::string, bool, bool, rp3d::Vector3, rp3d::Vector3, rp3d::Vector3>
		loadJoint3DComponent(std::ifstream &reader);

		static TexturedModel loadRender2DModel(const std::string &texturePath, Loader &loader);

		static void loadTerrainTextures(std::vector<std::string> &texturesPath, std::vector<Texture> &textures,
										Loader &loader, std::ifstream &reader);

		static Model loadAnimatedModel(entt::registry &registry, entt::entity entity,
									   Loader &loader, const std::string &modelName);
	};
}

#endif //SURVIVE_COMPONENTLOADER_H
