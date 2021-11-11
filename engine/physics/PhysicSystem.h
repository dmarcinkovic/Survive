//
// Created by david on 13. 10. 2021..
//

#ifndef SURVIVE_PHYSICSYSTEM_H
#define SURVIVE_PHYSICSYSTEM_H

#include <box2d/box2d.h>

#include "entt.hpp"

namespace Survive
{
	class PhysicSystem
	{
	public:
		static void update(entt::registry &registry);

		static void init(entt::registry &registry, b2World *world);

	private:
		static void initFixture(entt::registry &registry, entt::entity entity, b2Body *body);

		static void addBoxCollider(entt::registry &registry, entt::entity entity, b2Body *body);

		static void addEdgeCollider(entt::registry &registry, entt::entity entity, b2Body *body);

		static void addCircleCollider(entt::registry &registry, entt::entity entity, b2Body *body);

		static void addPolygonCollider(entt::registry &registry, entt::entity entity, b2Body *body);
	};
}

#endif //SURVIVE_PHYSICSYSTEM_H
