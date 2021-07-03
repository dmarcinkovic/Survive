//
// Created by david on 23. 06. 2021..
//

#include <iostream>

#include "SceneLoader.h"
#include "ComponentLoader.h"

//entity:entity_name:
//	component:Transform3DComponent:
//		position: 0.5f, 0.123f, 0.1f
//		scale: 13513
//		rotation: 124
//	end
//end
//	component:Render3DComponent:
//		modelName: "res/nesto"
//		textureName: "res/opet_nesto"
// 	end
//	component:RigidBody:
//		isTransparent: false
//  end

void Survive::SceneLoader::loadScene(entt::registry &registry, const std::string &filename)
{
	std::ifstream reader(filename);

	std::string line;
	while(std::getline(reader, line))
	{
		if (line.starts_with("entity:"))
		{
			loadEntity(registry, reader);
		}
	}
}

void Survive::SceneLoader::loadEntity(entt::registry &registry, std::ifstream &reader)
{
	std::string line;
	while (std::getline(reader, line))
	{
		if (line.starts_with("\tcomponent:"))
		{
			loadComponent(registry, reader, line);
		} else if (line.starts_with("end"))
		{
			break;
		}
	}
}

void Survive::SceneLoader::loadComponent(entt::registry &registry, std::ifstream &reader, const std::string &component)
{
	constexpr int componentLength = 11;
	std::string componentType = component.substr(componentLength);

	if (componentType == "BloomComponent")
	{
		ComponentLoader::loadBloomComponent(registry, reader);
	} else if (componentType == "ReflectionComponent")
	{
		ComponentLoader::loadReflectionComponent(registry, reader);
	} else if (componentType == "RefractionComponent")
	{
		ComponentLoader::loadRefractionComponent(registry, reader);
	} else if (componentType == "Render2DComponent")
	{
		ComponentLoader::loadRender2DComponent(registry, reader);
	} else if (componentType == "Render3DComponent")
	{
		ComponentLoader::loadRender3DComponent(registry, reader);
	} else if (componentType == "RigidBodyComponent")
	{
		ComponentLoader::loadRigidBodyComponent(registry, reader);
	} else if (componentType == "ShadowComponent")
	{
		ComponentLoader::loadShadowComponent(registry, reader);
	} else if (componentType == "Transform3DComponent")
	{
		ComponentLoader::loadTransformComponent(registry, reader);
	}
}
