//
// Created by david on 18. 07. 2021..
//

#ifndef SURVIVE_COMPONENTSERIALIZER_H
#define SURVIVE_COMPONENTSERIALIZER_H

#include <fstream>
#include <reactphysics3d/reactphysics3d.h>

#include "entt.hpp"

namespace Survive
{
	class ComponentSerializer
	{
	public:
		static void saveAnimationComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		static void saveBloomComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		static void saveReflectionComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		static void saveRefractionComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		static void saveRender2DComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		static void saveRender3DComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		static void saveMaterialComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		static void saveShadowComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		static void saveSoundComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		static void saveSpriteComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		static void saveSpriteSheetComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		static void saveTransform3DComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		static void saveTextComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		static void saveBoxCollider2DComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		static void saveCircleCollider2DComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		static void saveEdgeCollider2DComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		static void
		savePolygonCollider2DComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		static void saveHingeJoint2DComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		static void saveDistanceJoint2DComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		static void saveRigidBody2DComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		static void saveRigidBody3DComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		static void saveBoxCollider3DComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		static void
		saveCapsuleCollider3DComponent(entt::registry &registry, entt::entity &entity, std::ofstream &writer);

		static void
		saveSphereCollider3DComponent(entt::registry &registry, entt::entity &entity, std::ofstream &writer);

		static void
		saveConvexMeshCollider3DComponent(entt::registry &registry, entt::entity &entity, std::ofstream &writer);

		static void saveOutlineComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		static void saveHingeJoint3DComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		static void saveCharacterJoint3DComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

		static void saveFixedJoint3DComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer);

	private:
		static void printVec3(std::ofstream &writer, const char *label, const glm::vec3 &vec3);

		static void printVec3(std::ofstream &writer, const char *label, const rp3d::Vector3 &vec3);

		static void printVec4(std::ofstream &writer, const char *label, const glm::vec4 &vec4);

		static void printVec2(std::ofstream &writer, const char *label, const b2Vec2 &vec2);

		static void saveCollider2DComponent(std::ofstream &writer, const Collider2DComponent &colliderComponent);

		static void saveJoint3DComponent(std::ofstream &writer, const std::string &connectedBodyName,
										 bool enableCollision, bool isUsingLocalSpace, const rp3d::Vector3 &anchor,
										 const rp3d::Vector3 &localAnchor, const rp3d::Vector3 &anchorBody2);
	};
}

#endif //SURVIVE_COMPONENTSERIALIZER_H
