//
// Created by david on 03. 07. 2021..
//

#include <iostream>
#include "ObjParser.h"
#include "ComponentLoader.h"
#include "Components.h"

void Survive::ComponentLoader::loadBloomComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader)
{

}

void Survive::ComponentLoader::loadReflectionComponent(entt::registry &registry,
													   entt::entity entity, std::ifstream &reader)
{

}

void Survive::ComponentLoader::loadRefractionComponent(entt::registry &registry,
													   entt::entity entity, std::ifstream &reader)
{

}

void Survive::ComponentLoader::loadRender2DComponent(entt::registry &registry,
													 entt::entity entity, std::ifstream &reader)
{

}

void Survive::ComponentLoader::loadRender3DComponent(entt::registry &registry, entt::entity entity,
													 std::ifstream &reader, Loader &loader)
{
	std::string modelName, textureName;

	std::getline(reader, modelName);
	std::getline(reader, textureName);

	modelName = modelName.substr(modelName.find(':') + 1);
	textureName = textureName.substr(textureName.find(':') + 1);

	Render3DComponent render3DComponent(
			TexturedModel(ObjParser::loadObj(modelName.c_str(), loader),
						  Loader::loadTexture(textureName.c_str())));

	render3DComponent.textureName = textureName;
	render3DComponent.modelName = modelName;

	registry.emplace<Render3DComponent>(entity, std::move(render3DComponent));
}

void Survive::ComponentLoader::loadRigidBodyComponent(entt::registry &registry,
													  entt::entity entity, std::ifstream &reader)
{
	std::string isTransparent;

	std::getline(reader, isTransparent);
	isTransparent = isTransparent.substr(isTransparent.find(':') + 1);

	registry.emplace<RigidBodyComponent>(entity, std::stoi(isTransparent));
}

void Survive::ComponentLoader::loadShadowComponent(entt::registry &registry,
												   entt::entity entity, std::ifstream &reader)
{

}

void Survive::ComponentLoader::loadTransformComponent(entt::registry &registry,
													  entt::entity entity, std::ifstream &reader)
{

}
