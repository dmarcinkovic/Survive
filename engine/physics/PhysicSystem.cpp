//
// Created by david on 13. 10. 2021..
//

#include <glm/glm.hpp>

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

void Survive::PhysicSystem::init(entt::registry &registry, b2World *world)
{
	auto view = registry.view<RigidBody2DComponent, Transform3DComponent>();

	for (auto const &entity : view)
	{
		RigidBody2DComponent &rigidBody = view.get<RigidBody2DComponent>(entity);
		Transform3DComponent &transform = view.get<Transform3DComponent>(entity);

		float x = transform.position.x * Constants::BOX2D_SCALE;
		float y = transform.position.y * Constants::BOX2D_SCALE;

		rigidBody.bodyDefinition.position.Set(x, y);
		rigidBody.bodyDefinition.angle = glm::radians(transform.rotation.z);
		rigidBody.body = world->CreateBody(&rigidBody.bodyDefinition);

		initFixture(registry, entity, rigidBody.body);
	}
}

void Survive::PhysicSystem::initFixture(entt::registry &registry, entt::entity entity, b2Body *body)
{
	addBoxCollider(registry, entity, body);
	addEdgeCollider(registry, entity, body);
	addCircleCollider(registry, entity, body);
	addPolygonCollider(registry, entity, body);
}

void Survive::PhysicSystem::addBoxCollider(entt::registry &registry, entt::entity entity, b2Body *body)
{
	if (registry.any_of<BoxCollider2DComponent>(entity))
	{
		BoxCollider2DComponent &boxCollider = registry.get<BoxCollider2DComponent>(entity);
		boxCollider.fixtureDef.shape = &boxCollider.boxShape;
		body->CreateFixture(&boxCollider.fixtureDef);
	}
}

void Survive::PhysicSystem::addEdgeCollider(entt::registry &registry, entt::entity entity, b2Body *body)
{
	if (registry.any_of<EdgeCollider2DComponent>(entity))
	{
		EdgeCollider2DComponent &edgeCollider = registry.get<EdgeCollider2DComponent>(entity);
		edgeCollider.fixtureDef.shape = &edgeCollider.edgeShape;
		body->CreateFixture(&edgeCollider.fixtureDef);
	}
}

void Survive::PhysicSystem::addCircleCollider(entt::registry &registry, entt::entity entity, b2Body *body)
{
	if (registry.any_of<CircleCollider2DComponent>(entity))
	{
		CircleCollider2DComponent &circleCollider = registry.get<CircleCollider2DComponent>(entity);
		circleCollider.fixtureDef.shape = &circleCollider.circleShape;
		body->CreateFixture(&circleCollider.fixtureDef);
	}
}

void Survive::PhysicSystem::addPolygonCollider(entt::registry &registry, entt::entity entity, b2Body *body)
{
	if (registry.any_of<PolygonCollider2DComponent>(entity))
	{
		PolygonCollider2DComponent &polygonCollider = registry.get<PolygonCollider2DComponent>(entity);
		polygonCollider.fixtureDef.shape = &polygonCollider.polygonShape;
		body->CreateFixture(&polygonCollider.fixtureDef);
	}
}
