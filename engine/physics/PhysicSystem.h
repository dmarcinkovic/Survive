//
// Created by david on 13. 10. 2021..
//

#ifndef SURVIVE_PHYSICSYSTEM_H
#define SURVIVE_PHYSICSYSTEM_H

#include <reactphysics3d/reactphysics3d.h>
#include <box2d/box2d.h>

#include "entt.hpp"
#include "RigidBody3DComponent.h"
#include "Collider3DComponent.h"
#include "ConvexMeshCollider3DComponent.h"

namespace Survive
{
	class PhysicSystem
	{
	public:
		static void update(entt::registry &registry, b2World *world2D, rp3d::PhysicsWorld *world3D);

		static void init(entt::registry &registry, b2World *world2D, rp3d::PhysicsWorld *world3D,
						 rp3d::PhysicsCommon &physicsCommon);

	private:
		static void update3DPhysics(entt::registry &registry);

		static void update2DPhysics(entt::registry &registry);

		static void updateWorld(b2World *world2D, rp3d::PhysicsWorld *world3D);

		static void init2DPhysics(entt::registry &registry, b2World *world);

		static void
		init3DPhysics(entt::registry &registry, rp3d::PhysicsCommon &physicsCommon, rp3d::PhysicsWorld *world);

		static void initColliders2D(entt::registry &registry, entt::entity entity, b2Body *body);

		static void addBoxCollider2D(entt::registry &registry, entt::entity entity, b2Body *body);

		static void addEdgeCollider2D(entt::registry &registry, entt::entity entity, b2Body *body);

		static void addCircleCollider2D(entt::registry &registry, entt::entity entity, b2Body *body);

		static void addPolygonCollider2D(entt::registry &registry, entt::entity entity, b2Body *body);

		static void initializeRigidBody3D(RigidBody3DComponent &rigidBody);

		static void initColliders3D(entt::registry &registry, entt::entity entity, rp3d::PhysicsCommon &physicsCommon,
									rp3d::RigidBody *body);

		static void initBoxCollider3D(entt::registry &registry, entt::entity entity,
									  rp3d::PhysicsCommon &physicsCommon, rp3d::RigidBody *body);

		static void initSphereCollider3D(entt::registry &registry, entt::entity entity,
										 rp3d::PhysicsCommon &physicsCommon, rp3d::RigidBody *body);

		static void initCapsuleCollider3D(entt::registry &registry, entt::entity entity,
										  rp3d::PhysicsCommon &physicsCommon, rp3d::RigidBody *body);

		static void initCollider3DMaterial(rp3d::Material &material, const Collider3DComponent &collider3D);

		static void
		initMeshCollider3D(entt::registry &registry, entt::entity entity, rp3d::PhysicsCommon &physicsCommon,
						   rp3d::RigidBody *body);

		static void initHingeJoint2D(entt::registry &registry, entt::entity entity, b2World *world, b2Body *body);

		static void initDistanceJoint2D(entt::registry &registry, entt::entity entity, b2World *world, b2Body *body);

		static entt::entity findEntityWithTag(const std::string &tag, entt::registry &registry);

		static bool initConvexMeshComponent(ConvexMeshCollider3DComponent &meshCollider);

		static void initHingeJoint3D(entt::registry &registry, entt::entity entity, rp3d::PhysicsWorld *world,
									 rp3d::RigidBody *body);
	};
}

#endif //SURVIVE_PHYSICSYSTEM_H
