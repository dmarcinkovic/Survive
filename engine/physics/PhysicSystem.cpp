//
// Created by david on 13. 10. 2021..
//

#include <glm/glm.hpp>
#include <Box2D/Box2D.h>

#include "PhysicSystem.h"
#include "Components.h"
#include "Constants.h"

void Survive::PhysicSystem::update(entt::registry &registry)
{
	auto view = registry.view<RigidBody2DComponent, Transform3DComponent>();

	for (auto const &entity: view)
	{
		RigidBody2DComponent &rigidBody = view.get<RigidBody2DComponent>(entity);

		b2Body *body = rigidBody.body;

		b2Vec2 bodyPosition = body->GetPosition();
		Transform3DComponent &transform = view.get<Transform3DComponent>(entity);

		transform.position.x = bodyPosition.x / Constants::BOX2D_SCALE;
		transform.position.y = bodyPosition.y / Constants::BOX2D_SCALE;
		transform.rotation.z = glm::degrees(body->GetAngle());
	}
}
