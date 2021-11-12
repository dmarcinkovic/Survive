//
// Created by david on 13. 10. 2021..
//

#ifndef SURVIVE_PHYSICSYSTEM_H
#define SURVIVE_PHYSICSYSTEM_H

#include <reactphysics3d/reactphysics3d.h>
#include <box2d/box2d.h>

#include "entt.hpp"
#include "RigidBody3DComponent.h"

namespace Survive
{
	class PhysicSystem
	{
	public:
		static void update(entt::registry &registry);

		static void init(entt::registry &registry, b2World *world2D, rp3d::PhysicsWorld *world3D);

	private:
		static void update3DPhysics(entt::registry &registry);

		static void update2DPhysics(entt::registry &registry);

		static void init2DPhysics(entt::registry &registry, b2World *world);

		static void init3DPhysics(entt::registry &registry, rp3d::PhysicsWorld *world);

		static void initFixture(entt::registry &registry, entt::entity entity, b2Body *body);

		static void addBoxCollider(entt::registry &registry, entt::entity entity, b2Body *body);

		static void addEdgeCollider(entt::registry &registry, entt::entity entity, b2Body *body);

		static void addCircleCollider(entt::registry &registry, entt::entity entity, b2Body *body);

		static void addPolygonCollider(entt::registry &registry, entt::entity entity, b2Body *body);

		static void initializeRigidBody3D(RigidBody3DComponent &rigidBody);
	};
}

#endif //SURVIVE_PHYSICSYSTEM_H
