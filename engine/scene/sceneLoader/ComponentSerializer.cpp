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
		writer << "\tcomponent:AnimationComponent\n";
	}
}

void
Survive::ComponentSerializer::saveBloomComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer)
{
	if (registry.has<BloomComponent>(entity))
	{
		const BloomComponent &bloomComponent = registry.get<BloomComponent>(entity);

		writer << "\tcomponent:BloomComponent\n";
		writer << "\t\ttextureName:" << bloomComponent.textureName << '\n';
		writer << "\t\tbloomStrength:" << bloomComponent.bloomStrength << '\n';
	}
}

void Survive::ComponentSerializer::saveReflectionComponent(entt::registry &registry, entt::entity entity,
														   std::ofstream &writer)
{
	if (registry.has<ReflectionComponent>(entity))
	{
		writer << "\tcomponent:ReflectionComponent\n";
	}
}

void Survive::ComponentSerializer::saveRefractionComponent(entt::registry &registry, entt::entity entity,
														   std::ofstream &writer)
{
	if (registry.has<RefractionComponent>(entity))
	{
		writer << "\tcomponent:RefractionComponent\n";
	}
}

void Survive::ComponentSerializer::saveRender2DComponent(entt::registry &registry, entt::entity entity,
														 std::ofstream &writer)
{
	if (registry.has<Render2DComponent>(entity))
	{
		const Render2DComponent &renderComponent = registry.get<Render2DComponent>(entity);

		writer << "\tcomponent:Render2DComponent\n";
		writer << "\t\ttextureName:" << renderComponent.textureName << '\n';
	}
}

void Survive::ComponentSerializer::saveRender3DComponent(entt::registry &registry, entt::entity entity,
														 std::ofstream &writer)
{
	if (registry.has<Render3DComponent>(entity))
	{
		const Render3DComponent &renderComponent = registry.get<Render3DComponent>(entity);

		writer << "\tcomponent:Render3DComponent\n";
		writer << "\t\tmodelName:" << renderComponent.modelName << '\n';
		writer << "\t\ttextureName:" << renderComponent.textureName << '\n';
	}
}

void Survive::ComponentSerializer::saveRigidBodyComponent(entt::registry &registry, entt::entity entity,
														  std::ofstream &writer)
{
	if (registry.has<RigidBodyComponent>(entity))
	{
		const RigidBodyComponent &rigidBodyComponent = registry.get<RigidBodyComponent>(entity);

		writer << "\tcomponent:RigidBodyComponent\n";
		writer << "\t\tisTransparent:" << rigidBodyComponent.isTransparent << '\n';
	}
}

void Survive::ComponentSerializer::saveShadowComponent(entt::registry &registry,
													   entt::entity entity, std::ofstream &writer)
{
	if (registry.has<ShadowComponent>(entity))
	{
		const ShadowComponent &shadowComponent = registry.get<ShadowComponent>(entity);

		writer << "\tcomponent:ShadowComponent\n";
		writer << "\t\tloadShadow:" << shadowComponent.loadShadow << '\n';
	}
}

void Survive::ComponentSerializer::saveSoundComponent(entt::registry &registry,
													  entt::entity entity, std::ofstream &writer)
{
	if (registry.has<SoundComponent>(entity))
	{
		writer << "\tcomponent:SoundComponent\n";
	}
}

void
Survive::ComponentSerializer::saveSpriteComponent(entt::registry &registry, entt::entity entity, std::ofstream &writer)
{
	if (registry.has<SpriteComponent>(entity))
	{
		writer << "\tcomponent:SpriteComponent\n";
	}
}

void Survive::ComponentSerializer::saveSpriteSheetComponent(entt::registry &registry, entt::entity entity,
															std::ofstream &writer)
{
	if (registry.has<SpriteSheetComponent>(entity))
	{
		writer << "\tcomponent:SpriteSheetComponent\n";
	}
}

void Survive::ComponentSerializer::saveTransform3DComponent(entt::registry &registry, entt::entity entity,
															std::ofstream &writer)
{
	if (registry.has<Transform3DComponent>(entity))
	{
		const Transform3DComponent &transformComponent = registry.get<Transform3DComponent>(entity);

		writer << "\tcomponent:Transform3DComponent\n";

		printVec3(writer, "position", transformComponent.position);
		printVec3(writer, "scale", transformComponent.scale);
		printVec3(writer, "rotation", transformComponent.rotation);
	}
}

void Survive::ComponentSerializer::printVec3(std::ofstream &writer, const char *label, const glm::vec3 &vec3)
{
	writer << "\t\t" << label << ':' << vec3.x << ',' << vec3.y << ',' << vec3.z << '\n';
}