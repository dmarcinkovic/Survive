//
// Created by david on 03. 07. 2021..
//

#include "ObjParser.h"
#include "ComponentLoader.h"
#include "Components.h"

void Survive::ComponentLoader::loadAnimationComponent(entt::registry &registry,
													  entt::entity entity, std::ifstream &reader)
{

}

void Survive::ComponentLoader::loadBloomComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader)
{
	std::string textureName = parseLine(reader, "textureName");
	std::string bloomStrength = parseLine(reader, "bloomStrength");

	float strength = std::stof(bloomStrength);
	Texture bloomTexture = Loader::loadTexture(textureName.c_str());

	if (bloomTexture.isValidTexture())
	{
		BloomComponent bloom(bloomTexture, strength);
		bloom.textureName = textureName;

		registry.emplace<BloomComponent>(entity, bloom);
	}
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
													 entt::entity entity, std::ifstream &reader, Loader &loader)
{
	std::string textureName = parseLine(reader, "textureName");
	Texture image = Loader::loadTexture(textureName.c_str());

	if (image.isValidTexture())
	{
		Render2DComponent render2DComponent(TexturedModel(loader.renderQuad(), image));

		render2DComponent.textureName = textureName;
		registry.emplace<Render2DComponent>(entity, std::move(render2DComponent));
	}
}

void Survive::ComponentLoader::loadRender3DComponent(entt::registry &registry, entt::entity entity,
													 std::ifstream &reader, Loader &loader)
{
	std::string modelName = parseLine(reader, "modelName");
	std::string textureName = parseLine(reader, "textureName");

	Model model = ObjParser::loadObj(modelName.c_str(), loader);
	Texture texture = Loader::loadTexture(textureName.c_str());

	if (model.isValidModel() && texture.isValidTexture())
	{
		Render3DComponent render3DComponent(TexturedModel(model, texture));

		render3DComponent.textureName = textureName;
		render3DComponent.modelName = modelName;
		registry.emplace<Render3DComponent>(entity, std::move(render3DComponent));
	}
}

void Survive::ComponentLoader::loadRigidBodyComponent(entt::registry &registry,
													  entt::entity entity, std::ifstream &reader)
{
	std::string isTransparent = parseLine(reader, "isTransparent");

	registry.emplace<RigidBodyComponent>(entity, std::stoi(isTransparent));
}

void Survive::ComponentLoader::loadShadowComponent(entt::registry &registry,
												   entt::entity entity, std::ifstream &reader)
{
	std::string loadShadow = parseLine(reader, "loadShadow");

	registry.emplace<ShadowComponent>(entity, std::stoi(loadShadow));
}

void Survive::ComponentLoader::loadSoundComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader)
{

}

void Survive::ComponentLoader::loadSpriteComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader)
{

}

void
Survive::ComponentLoader::loadSpriteSheetComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader)
{

}

void Survive::ComponentLoader::loadTransformComponent(entt::registry &registry,
													  entt::entity entity, std::ifstream &reader)
{
	std::string position = parseLine(reader, "position");
	std::string scale = parseLine(reader, "scale");
	std::string rotation = parseLine(reader, "rotation");

	parseVec3(position);

	registry.emplace<Transform3DComponent>(entity, parseVec3(position), parseVec3(scale), parseVec3(rotation));
}

std::string Survive::ComponentLoader::parseLine(std::ifstream &reader, const char *text)
{
	std::string line;
	std::getline(reader, line);

	if (line.find(text) == std::string::npos)
	{
		throw std::runtime_error("Did not find required string in text");
	}

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
