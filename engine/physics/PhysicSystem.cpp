//
// Created by david on 13. 10. 2021..
//

#include <glm/glm.hpp>
#include <imgui.h>

#include "PhysicSystem.h"
#include "Components.h"
#include "Constants.h"

void Survive::PhysicSystem::update(entt::registry &registry, b2World *world)
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

	updateWorld(world);
}

void Survive::PhysicSystem::init(entt::registry &registry, b2World *world)
{
	auto view = registry.view<RigidBody2DComponent, Transform3DComponent>();

	for (auto const &entity: view)
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

	for (auto const &entity: view)
	{
		RigidBody2DComponent &rigidBody = view.get<RigidBody2DComponent>(entity);
		initHingeJoint(registry, entity, world, rigidBody.body);
		initDistanceJoint(registry, entity, world, rigidBody.body);
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

void Survive::PhysicSystem::updateWorld(b2World *world)
{
	float frameRate = ImGui::GetIO().Framerate;
	world->Step(1.0f / frameRate, 5, 5);
}

void Survive::PhysicSystem::initHingeJoint(entt::registry &registry, entt::entity entity, b2World *world, b2Body *body)
{
	if (registry.any_of<HingeJoint2DComponent>(entity))
	{
		HingeJoint2DComponent &hingeJoint = registry.get<HingeJoint2DComponent>(entity);
		hingeJoint.jointDef.bodyA = body;

		if (hingeJoint.connectedBody == entt::null ||
			!registry.any_of<RigidBody2DComponent>(hingeJoint.connectedBody))
		{
			b2BodyDef bodyDef;
			bodyDef.type = b2_staticBody;
			hingeJoint.jointDef.bodyB = world->CreateBody(&bodyDef);
		} else
		{
			RigidBody2DComponent &bodyB = registry.get<RigidBody2DComponent>(hingeJoint.connectedBody);
			hingeJoint.jointDef.bodyB = bodyB.body;
		}

		world->CreateJoint(&hingeJoint.jointDef);
	}
}

void
Survive::PhysicSystem::initDistanceJoint(entt::registry &registry, entt::entity entity, b2World *world, b2Body *body)
{
	if (registry.any_of<DistanceJoint2DComponent>(entity))
	{
		DistanceJoint2DComponent &distanceJoint = registry.get<DistanceJoint2DComponent>(entity);
		distanceJoint.jointDef.bodyA = body;

		if (distanceJoint.connectedBody == entt::null ||
			!registry.any_of<RigidBody2DComponent>(distanceJoint.connectedBody))
		{
			b2BodyDef bodyDef;
			bodyDef.type = b2_staticBody;
			distanceJoint.jointDef.bodyB = world->CreateBody(&bodyDef);
		} else
		{
			RigidBody2DComponent &bodyB = registry.get<RigidBody2DComponent>(distanceJoint.connectedBody);
			distanceJoint.jointDef.bodyB = bodyB.body;
		}

		world->CreateJoint(&distanceJoint.jointDef);
	}
}
