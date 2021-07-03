//
// Created by david on 23. 06. 2021..
//

#include <fstream>

#include "SceneLoader.h"

//entity_name:
//	Transform3DComponent:
//		position: 0.5f, 0.123f, 0.1f
//		scale: 13513
//		rotation: 124
//	Render3DComponent:
//		modelName: "res/nesto"
//		textureName: "res/opet_nesto"
//	RigidBody:
//		isTransparent: false


void SceneLoader::loadScene(entt::registry &registry, const std::string &filename)
{
	std::ifstream reader(filename);

	std::string line;
	std::string currentComponent;
	while(std::getline(reader, line))
	{

	}
}
