//
// Created by david on 13. 10. 2021..
//

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <imgui.h>

#include "PhysicSystem.h"
#include "Components.h"
#include "Constants.h"

void Survive::PhysicSystem::update(entt::registry &registry, b2World *world2D, rp3d::PhysicsWorld *world3D)
{
	update2DPhysics(registry);
	update3DPhysics(registry);

	updateWorld(world2D, world3D);
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

		const rp3d::Quaternion &rotation = transform.getOrientation();
		glm::quat quaternion{rotation.w, rotation.x, rotation.y, rotation.z};
		transformComponent.rotation = glm::degrees(glm::eulerAngles(quaternion));
	}
}

void Survive::PhysicSystem::init(entt::registry &registry, b2World *world2D, rp3d::PhysicsWorld *world3D,
								 rp3d::PhysicsCommon &physicsCommon)
{
	init2DPhysics(registry, world2D);
	init3DPhysics(registry, physicsCommon, world3D);
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

		initColliders2D(registry, entity, rigidBody.body);
	}

	for (auto const &entity: view)
	{
		RigidBody2DComponent &rigidBody = view.get<RigidBody2DComponent>(entity);
		initHingeJoint2D(registry, entity, world, rigidBody.body);
		initDistanceJoint2D(registry, entity, world, rigidBody.body);
	}
}

void Survive::PhysicSystem::init3DPhysics(entt::registry &registry, rp3d::PhysicsCommon &physicsCommon,
										  rp3d::PhysicsWorld *world)
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
		initColliders3D(registry, entity, physicsCommon, rigidBody.body);
		initializeRigidBody3D(rigidBody);
	}
}

void Survive::PhysicSystem::initColliders2D(entt::registry &registry, entt::entity entity, b2Body *body)
{
	addBoxCollider2D(registry, entity, body);
	addEdgeCollider2D(registry, entity, body);
	addCircleCollider2D(registry, entity, body);
	addPolygonCollider2D(registry, entity, body);
}

void Survive::PhysicSystem::addBoxCollider2D(entt::registry &registry, entt::entity entity, b2Body *body)
{
	if (registry.any_of<BoxCollider2DComponent>(entity))
	{
		BoxCollider2DComponent &boxCollider = registry.get<BoxCollider2DComponent>(entity);
		boxCollider.fixtureDef.shape = &boxCollider.boxShape;
		b2Fixture *fixture = body->CreateFixture(&boxCollider.fixtureDef);

		fixture->GetUserData().pointer = static_cast<uintptr_t>(entity);
	}
}

void Survive::PhysicSystem::addEdgeCollider2D(entt::registry &registry, entt::entity entity, b2Body *body)
{
	if (registry.any_of<EdgeCollider2DComponent>(entity))
	{
		EdgeCollider2DComponent &edgeCollider = registry.get<EdgeCollider2DComponent>(entity);
		edgeCollider.fixtureDef.shape = &edgeCollider.edgeShape;
		b2Fixture *fixture = body->CreateFixture(&edgeCollider.fixtureDef);

		fixture->GetUserData().pointer = static_cast<uintptr_t>(entity);
	}
}

void Survive::PhysicSystem::addCircleCollider2D(entt::registry &registry, entt::entity entity, b2Body *body)
{
	if (registry.any_of<CircleCollider2DComponent>(entity))
	{
		CircleCollider2DComponent &circleCollider = registry.get<CircleCollider2DComponent>(entity);
		circleCollider.fixtureDef.shape = &circleCollider.circleShape;
		b2Fixture *fixture = body->CreateFixture(&circleCollider.fixtureDef);

		fixture->GetUserData().pointer = static_cast<uintptr_t>(entity);
	}
}

void Survive::PhysicSystem::addPolygonCollider2D(entt::registry &registry, entt::entity entity, b2Body *body)
{
	if (registry.any_of<PolygonCollider2DComponent>(entity))
	{
		PolygonCollider2DComponent &polygonCollider = registry.get<PolygonCollider2DComponent>(entity);
		polygonCollider.fixtureDef.shape = &polygonCollider.polygonShape;
		b2Fixture *fixture = body->CreateFixture(&polygonCollider.fixtureDef);

		fixture->GetUserData().pointer = static_cast<uintptr_t>(entity);
	}
}

void
Survive::PhysicSystem::initHingeJoint2D(entt::registry &registry, entt::entity entity, b2World *world, b2Body *body)
{
	if (registry.any_of<HingeJoint2DComponent>(entity))
	{
		HingeJoint2DComponent &hingeJoint = registry.get<HingeJoint2DComponent>(entity);
		hingeJoint.jointDef.bodyA = body;

		if (hingeJoint.connectedBody == entt::null && hingeJoint.connectedBodyName != "none")
		{
			hingeJoint.connectedBody = findEntityWithTag(hingeJoint.connectedBodyName, registry);
		}

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
Survive::PhysicSystem::initDistanceJoint2D(entt::registry &registry, entt::entity entity, b2World *world, b2Body *body)
{
	if (registry.any_of<DistanceJoint2DComponent>(entity))
	{
		DistanceJoint2DComponent &distanceJoint = registry.get<DistanceJoint2DComponent>(entity);
		distanceJoint.jointDef.bodyA = body;

		if (distanceJoint.connectedBody == entt::null && distanceJoint.connectedBodyName != "none")
		{
			distanceJoint.connectedBody = findEntityWithTag(distanceJoint.connectedBodyName, registry);
		}

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

void Survive::PhysicSystem::initializeRigidBody3D(RigidBody3DComponent &rigidBody)
{
	rigidBody.body->setMass(rigidBody.mass);
	rigidBody.body->setType(rigidBody.bodyType);
	rigidBody.body->setAngularDamping(rigidBody.angularDrag);
	rigidBody.body->setLinearVelocity(rigidBody.linearVelocity);
	rigidBody.body->setLinearDamping(rigidBody.linearDamping);
	rigidBody.body->enableGravity(rigidBody.useGravity);
}

void Survive::PhysicSystem::initColliders3D(entt::registry &registry, entt::entity entity,
											rp3d::PhysicsCommon &physicsCommon, rp3d::RigidBody *body)
{
	initBoxCollider3D(registry, entity, physicsCommon, body);
	initSphereCollider3D(registry, entity, physicsCommon, body);
	initCapsuleCollider3D(registry, entity, physicsCommon, body);
	initMeshCollider3D(registry, entity, physicsCommon, body);
}

void Survive::PhysicSystem::initBoxCollider3D(entt::registry &registry, entt::entity entity,
											  rp3d::PhysicsCommon &physicsCommon, rp3d::RigidBody *body)
{
	if (registry.any_of<BoxCollider3DComponent>(entity))
	{
		BoxCollider3DComponent &boxCollider = registry.get<BoxCollider3DComponent>(entity);
		boxCollider.boxShape = physicsCommon.createBoxShape(boxCollider.position);

		rp3d::Transform transform(boxCollider.center, rp3d::Quaternion::identity());
		rp3d::Collider *collider = body->addCollider(boxCollider.boxShape, transform);
		body->updateLocalCenterOfMassFromColliders();

		initCollider3DMaterial(collider->getMaterial(), boxCollider);
	}
}

void Survive::PhysicSystem::initSphereCollider3D(entt::registry &registry, entt::entity entity,
												 rp3d::PhysicsCommon &physicsCommon, rp3d::RigidBody *body)
{
	if (registry.any_of<SphereCollider3DComponent>(entity))
	{
		SphereCollider3DComponent &sphereCollider = registry.get<SphereCollider3DComponent>(entity);
		sphereCollider.sphereShape = physicsCommon.createSphereShape(sphereCollider.radius);

		rp3d::Transform transform(sphereCollider.offset, rp3d::Quaternion::identity());
		rp3d::Collider *collider = body->addCollider(sphereCollider.sphereShape, transform);
		body->updateLocalCenterOfMassFromColliders();

		initCollider3DMaterial(collider->getMaterial(), sphereCollider);
	}
}

void Survive::PhysicSystem::updateWorld(b2World *world2D, rp3d::PhysicsWorld *world3D)
{
	float frameRate = ImGui::GetIO().Framerate;
	world2D->Step(1.0f / frameRate, 5, 5);

	world3D->update(1.0f / frameRate);
}

void Survive::PhysicSystem::initCollider3DMaterial(rp3d::Material &material, const Collider3DComponent &collider3D)
{
	material.setBounciness(collider3D.bounciness);
	material.setFrictionCoefficient(collider3D.friction);
}

void Survive::PhysicSystem::initCapsuleCollider3D(entt::registry &registry, entt::entity entity,
												  rp3d::PhysicsCommon &physicsCommon, rp3d::RigidBody *body)
{
	if (registry.any_of<CapsuleCollider3DComponent>(entity))
	{
		CapsuleCollider3DComponent &capsuleCollider = registry.get<CapsuleCollider3DComponent>(entity);

		float radius = capsuleCollider.radius;
		float height = capsuleCollider.height;
		capsuleCollider.capsuleShape = physicsCommon.createCapsuleShape(radius, height);

		rp3d::Transform transform(capsuleCollider.center, rp3d::Quaternion::identity());
		rp3d::Collider *collider = body->addCollider(capsuleCollider.capsuleShape, transform);
		body->updateLocalCenterOfMassFromColliders();

		initCollider3DMaterial(collider->getMaterial(), capsuleCollider);
	}
}

void Survive::PhysicSystem::initMeshCollider3D(entt::registry &registry, entt::entity entity,
											   rp3d::PhysicsCommon &physicsCommon, rp3d::RigidBody *body)
{
	if (registry.any_of<ConvexMeshCollider3DComponent>(entity))
	{
		ConvexMeshCollider3DComponent &meshCollider = registry.get<ConvexMeshCollider3DComponent>(entity);

		initConvexMeshComponent(meshCollider);

		meshCollider.polyhedronMesh = physicsCommon.createPolyhedronMesh(meshCollider.polygonVertexArray);
		meshCollider.meshShape = physicsCommon.createConvexMeshShape(meshCollider.polyhedronMesh);

		rp3d::Collider *collider = body->addCollider(meshCollider.meshShape, rp3d::Transform::identity());
		body->updateLocalCenterOfMassFromColliders();

		initCollider3DMaterial(collider->getMaterial(), meshCollider);
	}
}

entt::entity Survive::PhysicSystem::findEntityWithTag(const std::string &tag, entt::registry &registry)
{
	auto view = registry.view<TagComponent>();

	for (const auto &entity: view)
	{
		const TagComponent &tagComponent = view.get<TagComponent>(entity);

		if (tagComponent.tag == tag)
		{
			return entity;
		}
	}

	return entt::null;
}

void Survive::PhysicSystem::initConvexMeshComponent(Survive::ConvexMeshCollider3DComponent &meshCollider)
{
	int numberOfFaces = meshCollider.numberOfFaces;
	meshCollider.polygonFaces = std::vector<rp3d::PolygonVertexArray::PolygonFace>(numberOfFaces);

	int numberOfVerticesInFace = static_cast<int>(meshCollider.indices.size()) / numberOfFaces;
	int numberOfVertices = meshCollider.numberOfVertices;

	for (int face = 0; face < numberOfFaces; ++face)
	{
		meshCollider.polygonFaces[face].indexBase = face * numberOfVerticesInFace;
		meshCollider.polygonFaces[face].nbVertices = numberOfVerticesInFace;
	}

	auto vertexDataType = ConvexMeshCollider3DComponent::VERTEX_TYPE;
	auto indexDataType = ConvexMeshCollider3DComponent::INDEX_TYPE;

	std::size_t verticesStride = (meshCollider.vertices.size() / numberOfVertices) * sizeof(float);
	meshCollider.polygonVertexArray = new rp3d::PolygonVertexArray(numberOfVertices, meshCollider.vertices.data(),
																   static_cast<int>(verticesStride),
																   meshCollider.indices.data(),
																   sizeof(int), numberOfFaces,
																   meshCollider.polygonFaces.data(),
																   vertexDataType, indexDataType);
}
