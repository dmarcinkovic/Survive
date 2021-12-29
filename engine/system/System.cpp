//
// Created by david on 22. 11. 2021..
//

#include "PhysicSystem.h"
#include "AudioSystem.h"
#include "AnimationSystem.h"
#include "SkyRotateSystem.h"
#include "SpriteUpdate.h"
#include "System.h"

void Survive::System::update(entt::registry &registry, b2World *world2D, rp3d::PhysicsWorld *world3D)
{
	PhysicSystem::update(registry, world2D, world3D);
	AudioSystem::update(registry);
	AnimationSystem::update(registry);
	// TODO change this
//	SkyRotateSystem::rotateSky(registry, sky);
	SpriteUpdate::update(registry);
}
