//
// Created by david on 23. 06. 2021..
//

#include "SceneLoader.h"
#include "ComponentLoader.h"

void Survive::SceneLoader::loadScene(entt::registry &registry, const std::string &filename)
{
	std::ifstream reader(filename);

	std::string line;
	while (std::getline(reader, line))
	{
		if (line.starts_with("entity:"))
		{
			loadEntity(registry, reader, line);
		}
	}
}

entt::entity Survive::SceneLoader::createEntity(entt::registry &registry, const std::string &tag)
{
	constexpr int entityLength = 7;

	auto entity = registry.create();
	registry.emplace<TagComponent>(entity, tag.substr(entityLength));

	return entity;
}

void Survive::SceneLoader::loadEntity(entt::registry &registry, std::ifstream &reader, const std::string &tag)
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

void Survive::SceneLoader::loadComponent(entt::registry &registry, entt::entity entity,
										 std::ifstream &reader, const std::string &component)
{
	constexpr int componentLength = 11;
	std::string componentType = component.substr(componentLength);

	if (componentType == "BloomComponent")
	{
		ComponentLoader::loadBloomComponent(registry, entity, reader);
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
	} else if (componentType == "RigidBodyComponent")
	{
		ComponentLoader::loadRigidBodyComponent(registry, entity, reader);
	} else if (componentType == "ShadowComponent")
	{
		ComponentLoader::loadShadowComponent(registry, entity, reader);
	} else if (componentType == "Transform3DComponent")
	{
		ComponentLoader::loadTransformComponent(registry, entity, reader);
	}
}
