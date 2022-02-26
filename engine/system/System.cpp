//
// Created by david on 22. 11. 2021..
//

#include "PhysicSystem.h"
#include "AudioSystem.h"
#include "AnimationSystem.h"
#include "SkyRotateSystem.h"
#include "SpriteUpdate.h"
#include "ScriptingSystem.h"
#include "System.h"

void Survive::System::update(entt::registry &registry, b2World *world)
{
	PhysicSystem::update(registry, world);
	AudioSystem::update(registry);
	AnimationSystem::update(registry);
	// TODO change this
//	SkyRotateSystem::rotateSky(registry, sky);
	SpriteUpdate::update(registry);
	ScriptingSystem::update(registry);
}

void Survive::System::init(entt::registry &registry, EventHandler &eventHandler, b2World *world)
{
	PhysicSystem::init(registry, world);
	ScriptingSystem::init(registry, eventHandler);
}

void Survive::System::destroy(entt::registry &registry)
{
	ScriptingSystem::destroy(registry);
}
