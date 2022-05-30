//
// Created by david on 22. 11. 2021..
//

#include "PhysicSystem.h"
#include "AudioSystem.h"
#include "AnimationSystem.h"
#include "SpriteUpdate.h"
#include "ScriptingSystem.h"
#include "ParticleSystem.h"
#include "System.h"

void Survive::System::update(entt::registry &registry, b2World *world2D, rp3d::PhysicsWorld *world3D)
{
	PhysicSystem::update(registry, world2D, world3D);
	AudioSystem::update(registry);
	AnimationSystem::update(registry);
	SpriteUpdate::update(registry);
	ParticleSystem::update(registry);
	ScriptingSystem::update(registry);
}

void Survive::System::init(entt::registry &registry, EventHandler &eventHandler, b2World *world2D,
						   rp3d::PhysicsWorld *world3D, rp3d::PhysicsCommon &physicsCommon)
{
	PhysicSystem::init(registry, world2D, world3D, physicsCommon);
	ScriptingSystem::init(registry, eventHandler);
}

void Survive::System::destroy(entt::registry &registry)
{
	ScriptingSystem::destroy(registry);
}
