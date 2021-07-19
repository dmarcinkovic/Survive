//
// Created by david on 18. 07. 2021..
//

#include "Components.h"
#include "ComponentSerializer.h"

void Survive::ComponentSerializer::saveAnimationComponent(entt::registry &registry, entt::entity entity,
														  std::ofstream &writer)
{
	if (registry.has<AnimationComponent>(entity))
	{

	}
}

void
Survive::ComponentSerializer::saveBloomComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer)
{
	if (registry.has<BloomComponent>(entity))
	{

	}
}

void Survive::ComponentSerializer::saveReflectionComponent(entt::registry &registry, entt::entity entity,
														   std::ofstream &writer)
{
	if (registry.has<ReflectionComponent>(entity))
	{

	}
}

void Survive::ComponentSerializer::saveRefractionComponent(entt::registry &registry, entt::entity entity,
														   std::ofstream &writer)
{
	if (registry.has<RefractionComponent>(entity))
	{

	}
}

void Survive::ComponentSerializer::saveRender2DComponent(entt::registry &registry, entt::entity entity,
														 std::ofstream &writer)
{
	if (registry.has<Render2DComponent>(entity))
	{

	}
}

void Survive::ComponentSerializer::saveRender3DComponent(entt::registry &registry, entt::entity entity,
														 std::ofstream &writer)
{
	if (registry.has<Render3DComponent>(entity))
	{

	}
}

void Survive::ComponentSerializer::saveRigidBodyComponent(entt::registry &registry, entt::entity entity,
														  std::ofstream &writer)
{
	if (registry.has<RigidBodyComponent>(entity))
	{

	}
}

void Survive::ComponentSerializer::saveShadowComponent(entt::registry &registry,
													   entt::entity entity, std::ofstream &writer)
{
	if (registry.has<ShadowComponent>(entity))
	{

	}
}

void Survive::ComponentSerializer::saveSoundComponent(entt::registry &registry,
													  entt::entity entity, std::ofstream &writer)
{
	if (registry.has<SoundComponent>(entity))
	{

	}
}

void
Survive::ComponentSerializer::saveSpriteComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer)
{
	if (registry.has<SpriteComponent>(entity))
	{

	}
}

void Survive::ComponentSerializer::saveSpriteSheetComponent(entt::registry &registry, entt::entity entity,
															std::ofstream &writer)
{
	if (registry.has<SpriteSheetComponent>(entity))
	{

	}
}

void Survive::ComponentSerializer::saveTransform3DComponent(entt::registry &registry, entt::entity entity,
															std::ofstream &writer)
{
	if (registry.has<Transform3DComponent>(entity))
	{

	}
}
