//
// Created by david on 23. 06. 2021..
//

#include "SceneSerializer.h"
#include "ComponentLoader.h"
#include "ComponentSerializer.h"

void Survive::SceneSerializer::loadScene(entt::registry &registry, const std::string &filename)
{
	std::ifstream reader(filename);

	registry.each([&](const entt::entity entity) {
		registry.destroy(entity);
	});

	std::string line;
	while (std::getline(reader, line))
	{
		if (line.starts_with("entity:"))
		{
			loadEntity(registry, reader, line);
		}
	}

	reader.close();
}

void Survive::SceneSerializer::saveScene(entt::registry &registry, const std::string &filename)
{
	std::ofstream writer(filename);

	registry.each([&](const entt::entity &entity) {
		if (registry.any_of<TagComponent>(entity))
		{
			const TagComponent &tag = registry.get<TagComponent>(entity);
			writer << "entity:" << tag.tag << '\n';

			saveComponents(registry, entity, writer);
			writer << "end\n";
		}
	});

	writer.close();
}

entt::entity Survive::SceneSerializer::createEntity(entt::registry &registry, const std::string &tag)
{
	constexpr int entityLength = 7;

	auto entity = registry.create();
	registry.emplace<TagComponent>(entity, tag.substr(entityLength));

	return entity;
}

void Survive::SceneSerializer::loadEntity(entt::registry &registry, std::ifstream &reader, const std::string &tag)
{
	entt::entity entity = createEntity(registry, tag);

	std::string line;
	while (std::getline(reader, line))
	{
		if (line.starts_with("\tcomponent:"))
		{
			loadComponent(registry, entity, reader, line);
		} else if (line.starts_with("end"))
		{
			break;
		}
	}
}

void Survive::SceneSerializer::loadComponent(entt::registry &registry, entt::entity entity,
											 std::ifstream &reader, const std::string &component)
{
	constexpr int componentLength = 11;
	std::string componentType = component.substr(componentLength);

	try
	{
		if (componentType == "AnimationComponent")
		{

		} else if (componentType == "BloomComponent")
		{
			ComponentLoader::loadBloomComponent(registry, entity, reader, m_Loader);
		} else if (componentType == "ReflectionComponent")
		{
			ComponentLoader::loadReflectionComponent(registry, entity, reader);
		} else if (componentType == "RefractionComponent")
		{
			ComponentLoader::loadRefractionComponent(registry, entity, reader);
		} else if (componentType == "Render2DComponent")
		{
			ComponentLoader::loadRender2DComponent(registry, entity, reader, m_Loader);
		} else if (componentType == "Render3DComponent")
		{
			ComponentLoader::loadRender3DComponent(registry, entity, reader, m_Loader);
		} else if (componentType == "MaterialComponent")
		{
			ComponentLoader::loadRigidBodyComponent(registry, entity, reader);
		} else if (componentType == "ShadowComponent")
		{
			ComponentLoader::loadShadowComponent(registry, entity, reader);
		} else if (componentType == "SoundComponent")
		{
			ComponentLoader::loadSoundComponent(registry, entity, reader, m_AudioMaster);
		} else if (componentType == "SpriteComponent")
		{
			ComponentLoader::loadSpriteComponent(registry, entity, reader);
		} else if (componentType == "SpriteSheetComponent")
		{
			ComponentLoader::loadSpriteSheetComponent(registry, entity, reader);
		} else if (componentType == "Transform3DComponent")
		{
			ComponentLoader::loadTransformComponent(registry, entity, reader);
		} else if (componentType == "TextComponent")
		{
			ComponentLoader::loadTextComponent(registry, entity, reader, m_Loader);
		}
	} catch (const std::exception &ignorable)
	{}
}

void Survive::SceneSerializer::saveComponents(entt::registry &registry, entt::entity entity, std::ofstream &writer)
{
	ComponentSerializer::saveAnimationComponent(registry, entity, writer);
	ComponentSerializer::saveBloomComponent(registry, entity, writer);
	ComponentSerializer::saveReflectionComponent(registry, entity, writer);
	ComponentSerializer::saveRefractionComponent(registry, entity, writer);
	ComponentSerializer::saveRender2DComponent(registry, entity, writer);
	ComponentSerializer::saveRender3DComponent(registry, entity, writer);
	ComponentSerializer::saveRigidBodyComponent(registry, entity, writer);
	ComponentSerializer::saveShadowComponent(registry, entity, writer);
	ComponentSerializer::saveSoundComponent(registry, entity, writer);
	ComponentSerializer::saveSpriteComponent(registry, entity, writer);
	ComponentSerializer::saveSpriteSheetComponent(registry, entity, writer);
	ComponentSerializer::saveTransform3DComponent(registry, entity, writer);
	ComponentSerializer::saveTextComponent(registry, entity, writer);
}
