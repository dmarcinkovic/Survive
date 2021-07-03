//
// Created by david on 23. 06. 2021..
//

#include <iostream>

#include "SceneLoader.h"

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

void SceneLoader::loadScene(entt::registry &registry, const std::string &filename)
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

void SceneLoader::loadEntity(entt::registry &registry, std::ifstream &reader)
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

void SceneLoader::loadComponent(entt::registry &registry, std::ifstream &reader, const std::string &component)
{
	std::string componentType = component.substr(11);
	std::cout << "Component type: " << componentType << '\n';

	if (componentType == "BloomComponent")
	{

	} else if (componentType == "ReflectionComponent")
	{

	} else if (componentType == "RefractionComponent")
	{

	} else if (componentType == "Render2DComponent")
	{

	} else if (componentType == "Render3DComponent")
	{

	} else if (componentType == "RigidBodyComponent")
	{

	} else if (componentType == "ShadowComponent")
	{

	} else if (componentType == "Transform3DComponent")
	{

	}
}
