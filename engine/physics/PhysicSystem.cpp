//
// Created by david on 13. 10. 2021..
//

#include <glm/glm.hpp>

#include "PhysicSystem.h"
#include "Components.h"
#include "Constants.h"

void Survive::PhysicSystem::update(entt::registry &registry)
{
	update2DPhysics(registry);
	update3DPhysics(registry);
}

void Survive::PhysicSystem::update2DPhysics(entt::registry &registry)
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

void Survive::PhysicSystem::update3DPhysics(entt::registry &registry)
{
	auto view = registry.view<RigidBody3DComponent, Transform3DComponent>();

	for (auto const &entity: view)
	{
		RigidBody3DComponent &rigidBody = view.get<RigidBody3DComponent>(entity);

		rp3d::RigidBody *body = rigidBody.body;

		const rp3d::Transform &transform = body->getTransform();
		Transform3DComponent &transformComponent = view.get<Transform3DComponent>(entity);

		const rp3d::Vector3 &position = transform.getPosition();
		transformComponent.position = glm::vec3{position.x, position.y, position.z};

		// TODO update rotation
	}
}

void Survive::PhysicSystem::init(entt::registry &registry, b2World *world2D, rp3d::PhysicsWorld *world3D)
{
	init2DPhysics(registry, world2D);
	init3DPhysics(registry, world3D);
}

void Survive::PhysicSystem::init2DPhysics(entt::registry &registry, b2World *world)
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
}

void Survive::PhysicSystem::init3DPhysics(entt::registry &registry, rp3d::PhysicsWorld *world)
{
	auto view = registry.view<RigidBody3DComponent, Transform3DComponent>();

	for (auto const &entity: view)
	{
		RigidBody3DComponent &rigidBody = view.get<RigidBody3DComponent>(entity);
		Transform3DComponent &transform = view.get<Transform3DComponent>(entity);

		rp3d::Vector3 position{transform.position.x, transform.position.y, transform.position.z};

		glm::vec3 rotation = glm::radians(transform.rotation);
		rp3d::Quaternion orientation = rp3d::Quaternion::fromEulerAngles(rotation.x, rotation.y, rotation.z);

		rigidBody.body = world->createRigidBody({position, orientation});

		rigidBody.body->setType(rigidBody.bodyType);
		rigidBody.body->setMass(rigidBody.mass);
		rigidBody.body->setAngularDamping(rigidBody.angularDrag);
		rigidBody.body->setLinearVelocity(rigidBody.linearVelocity);
		rigidBody.body->setLinearDamping(rigidBody.linearDamping);
		rigidBody.body->enableGravity(rigidBody.useGravity);
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
