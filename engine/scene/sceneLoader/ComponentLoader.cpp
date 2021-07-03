//
// Created by david on 03. 07. 2021..
//

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
	std::string modelName = getName(reader);
	std::string textureName = getName(reader);

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
	std::string isTransparent = getName(reader);

	registry.emplace<RigidBodyComponent>(entity, std::stoi(isTransparent));
}

void Survive::ComponentLoader::loadShadowComponent(entt::registry &registry,
												   entt::entity entity, std::ifstream &reader)
{

}

void Survive::ComponentLoader::loadTransformComponent(entt::registry &registry,
													  entt::entity entity, std::ifstream &reader)
{
	std::string position = getName(reader);
	std::string scale = getName(reader);
	std::string rotation = getName(reader);

	parseVec3(position);

	registry.emplace<Transform3DComponent>(entity, parseVec3(position), parseVec3(scale), parseVec3(rotation));
}

std::string Survive::ComponentLoader::getName(std::ifstream &reader)
{
	std::string line;
	std::getline(reader, line);

	std::string name = line.substr(line.find(':') + 1);
	return name;
}

glm::vec3 Survive::ComponentLoader::parseVec3(const std::string &vec3)
{
	size_t start = vec3.find(',');
	size_t end = vec3.find_last_of(',');

	float x = std::stof(vec3.substr(0, start));
	float y = std::stof(vec3.substr(start + 1, end - start - 1));
	float z = std::stof(vec3.substr(end + 1));

	return glm::vec3(x, y, z);
}
