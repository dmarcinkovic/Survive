//
// Created by david on 03. 07. 2021..
//

#include "ObjParser.h"
#include "ComponentLoader.h"
#include "Components.h"
#include "Util.h"

void Survive::ComponentLoader::loadAnimationComponent(entt::registry &registry,
													  entt::entity entity, std::ifstream &reader)
{

}

void Survive::ComponentLoader::loadBloomComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader,
												  Loader &loader)
{
	std::string textureName = parseLine(reader, "textureName");
	std::string bloomStrength = parseLine(reader, "bloomStrength");

	float strength = std::stof(bloomStrength);
	Texture bloomTexture = loader.loadTexture(textureName.c_str());

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
	std::string reflectionFactor = parseLine(reader, "reflectionFactor");
	float factor = std::stof(reflectionFactor);

	registry.emplace<ReflectionComponent>(entity, factor);
}

void Survive::ComponentLoader::loadRefractionComponent(entt::registry &registry,
													   entt::entity entity, std::ifstream &reader)
{
	std::string refractiveIndex = parseLine(reader, "refractiveIndex");
	std::string refractiveFactor = parseLine(reader, "refractiveFactor");

	float index = std::stof(refractiveIndex);
	float factor = std::stof(refractiveFactor);

	registry.emplace<RefractionComponent>(entity, index, factor);
}

void Survive::ComponentLoader::loadRender2DComponent(entt::registry &registry, entt::entity entity,
													 std::ifstream &reader, Loader &loader)
{
	std::string textureName = parseLine(reader, "textureName");
	Model model = loader.renderQuad();

	Texture image;
	try
	{
		image = loader.loadTexture(textureName.c_str());
	} catch (const std::runtime_error &error)
	{}

	Render2DComponent render2DComponent(TexturedModel(model, image));

	render2DComponent.textureName = textureName;
	registry.emplace<Render2DComponent>(entity, std::move(render2DComponent));
}

void Survive::ComponentLoader::loadRender3DComponent(entt::registry &registry, entt::entity entity,
													 std::ifstream &reader, Loader &loader)
{
	std::string modelName = parseLine(reader, "modelName");
	std::string textureName = parseLine(reader, "textureName");

	Model model = ObjParser::loadObj(modelName, loader);

	Texture texture;
	try
	{
		texture = loader.loadTexture(textureName.c_str());
	} catch (const std::runtime_error &error)
	{}

	Render3DComponent render3DComponent(TexturedModel(model, texture));

	if (texture.isValidTexture())
	{
		render3DComponent.textureName = textureName;
	}

	render3DComponent.modelName = modelName;
	registry.emplace<Render3DComponent>(entity, std::move(render3DComponent));
}

void Survive::ComponentLoader::loadMaterialComponent(entt::registry &registry, entt::entity entity,
													 std::ifstream &reader, Loader &loader)
{
	std::string isTransparent = parseLine(reader, "isTransparent");
	std::string useNormalMapping = parseLine(reader, "useNormalMapping");
	std::string normalMapPath = parseLine(reader, "normalMap");

	bool enableNormalMapping = std::stoi(useNormalMapping);

	if (enableNormalMapping)
	{
		Texture normalMap = loader.loadTexture(normalMapPath.c_str());

		MaterialComponent material(std::stoi(isTransparent), enableNormalMapping, normalMap);
		material.normalMapPath = normalMapPath;

		registry.emplace<MaterialComponent>(entity, material);
	} else
	{
		registry.emplace<MaterialComponent>(entity, std::stoi(isTransparent));
	}
}

void Survive::ComponentLoader::loadShadowComponent(entt::registry &registry,
												   entt::entity entity, std::ifstream &reader)
{
	std::string loadShadow = parseLine(reader, "loadShadow");

	registry.emplace<ShadowComponent>(entity, std::stoi(loadShadow));
}

void Survive::ComponentLoader::loadSoundComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader,
												  AudioMaster &audioMaster)
{
	std::string soundFile = parseLine(reader, "soundFile");

	float pitch = std::stof(parseLine(reader, "pitch"));
	float gain = std::stof(parseLine(reader, "gain"));

	bool playOnLoop = std::stoi(parseLine(reader, "playOnLoop"));
	bool play = std::stoi(parseLine(reader, "play"));

	ALint soundTrack = audioMaster.loadSound(soundFile.c_str());
	Source source(gain, pitch);

	registry.emplace<SoundComponent>(entity, soundTrack, source, soundFile, pitch, gain, playOnLoop, play);
}

void Survive::ComponentLoader::loadSpriteComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader)
{
	std::string colorString = parseLine(reader, "color");
	glm::vec4 color = parseVec4(colorString);

	registry.emplace<SpriteComponent>(entity, color);
}

void Survive::ComponentLoader::loadSpriteSheetComponent(entt::registry &registry,
														entt::entity entity, std::ifstream &reader)
{
	int rows = std::stoi(parseLine(reader, "rows"));
	int cols = std::stoi(parseLine(reader, "cols"));

	int startIndex = std::stoi(parseLine(reader, "startIndex"));
	int endIndex = std::stoi(parseLine(reader, "endIndex"));

	int spritesInSecond = std::stoi(parseLine(reader, "spritesInSecond"));
	int numberOfEpochs = std::stoi(parseLine(reader, "numberOfEpochs"));

	bool animate = std::stoi(parseLine(reader, "animate"));

	registry.emplace<SpriteSheetComponent>(entity, rows, cols, spritesInSecond, startIndex,
										   endIndex, numberOfEpochs, animate);
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

	std::string pattern(text);
	if (line.find(pattern + ':') == std::string::npos)
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

	return {x, y, z};
}

b2Vec2 Survive::ComponentLoader::parseVec2(const std::string &vec2)
{
	size_t start = vec2.find(',');

	float x = std::stof(vec2.substr(0, start));
	float y = std::stof(vec2.substr(start + 1));

	return {x, y};
}

glm::vec4 Survive::ComponentLoader::parseVec4(const std::string &vec4)
{
	std::vector<std::string> numbers = Util::split(vec4, ',');

	float x = std::stof(numbers[0]);
	float y = std::stof(numbers[1]);
	float z = std::stof(numbers[2]);
	float w = std::stof(numbers[3]);

	return {x, y, z, w};
}

void Survive::ComponentLoader::loadTextComponent(entt::registry &registry, entt::entity entity,
												 std::ifstream &reader, Loader &loader)
{
	std::string string = parseLine(reader, "text");
	std::string fontFile = parseLine(reader, "fontFile");
	std::string textureAtlas = parseLine(reader, "textureAtlas");

	auto font = getFont(fontFile, textureAtlas, loader);

	if (!font)
	{
		return;
	}

	float lineSpacing = std::stof(parseLine(reader, "lineSpacing"));
	bool centerText = std::stoi(parseLine(reader, "centerText"));

	bool addBorder = std::stoi(parseLine(reader, "addBorder"));
	float borderWidth = std::stof(parseLine(reader, "borderWidth"));
	glm::vec3 borderColor = parseVec3(parseLine(reader, "borderColor"));

	Text text(string, font.value(), lineSpacing, centerText, addBorder, borderWidth, borderColor);
	text.loadTexture(loader);

	TextComponent textComponent(text);
	textComponent.textureAtlas = textureAtlas;
	textComponent.fontFile = fontFile;

	registry.emplace<TextComponent>(entity, textComponent);
}

void Survive::ComponentLoader::loadBox2DColliderComponent(entt::registry &registry, entt::entity entity,
														  std::ifstream &reader)
{
	float width = std::stof(parseLine(reader, "width"));
	float height = std::stof(parseLine(reader, "height"));
	b2Vec2 center = parseVec2(parseLine(reader, "center"));

	auto [mass, friction, elasticity] = loadCollider2DComponent(reader);

	if (width < 0 || height < 0 || mass < 0 || friction < 0 || friction > 1 || elasticity < 0 || elasticity > 1)
	{
		return;
	}

	BoxCollider2DComponent boxCollider(width, height, mass, friction, elasticity);
	boxCollider.center = center;

	registry.emplace<BoxCollider2DComponent>(entity, boxCollider);
}

void Survive::ComponentLoader::loadCircleCollider2DComponent(entt::registry &registry, entt::entity entity,
															 std::ifstream &reader)
{
	float radius = std::stof(parseLine(reader, "radius"));
	b2Vec2 center = parseVec2(parseLine(reader, "center"));

	auto [mass, friction, elasticity] = loadCollider2DComponent(reader);

	if (radius < 0 || mass < 0 || friction < 0 || friction > 1 || elasticity < 0 || elasticity > 1)
	{
		return;
	}

	CircleCollider2DComponent circleCollider(radius, mass, friction, elasticity);
	circleCollider.circleShape.m_p = center;

	registry.emplace<CircleCollider2DComponent>(entity, circleCollider);
}

void Survive::ComponentLoader::loadPolygonCollider2DComponent(entt::registry &registry, entt::entity entity,
															  std::ifstream &reader)
{
	int numberOfPoints = std::stoi(parseLine(reader, "numberOfPoints"));

	std::vector<b2Vec2> points;
	for (int i = 0; i < numberOfPoints; ++i)
	{
		std::string name = "point" + std::to_string(i + 1);
		b2Vec2 point = parseVec2(parseLine(reader, name.c_str()));
		points.emplace_back(point.x, point.y);
	}

	auto [mass, friction, elasticity] = loadCollider2DComponent(reader);

	if (mass < 0 || friction < 0 || friction > 1 || elasticity < 0 || elasticity > 1)
	{
		return;
	}

	registry.emplace<PolygonCollider2DComponent>(entity, points, mass, friction, elasticity);
}

void Survive::ComponentLoader::loadEdgeCollider2DComponent(entt::registry &registry, entt::entity entity,
														   std::ifstream &reader)
{
	b2Vec2 point1 = parseVec2(parseLine(reader, "point1"));
	b2Vec2 point2 = parseVec2(parseLine(reader, "point2"));

	auto [mass, friction, elasticity] = loadCollider2DComponent(reader);

	if (mass < 0 || friction < 0 || friction > 1 || elasticity < 0 || elasticity > 1)
	{
		return;
	}

	registry.emplace<EdgeCollider2DComponent>(entity, point1, point2, mass, friction, elasticity);
}

void Survive::ComponentLoader::loadHingeJoint2DComponent(entt::registry &registry, entt::entity entity,
														 std::ifstream &reader)
{
	std::string connectedBodyName = parseLine(reader, "connectedBody");

	b2Vec2 anchorA = parseVec2(parseLine(reader, "anchorA"));
	b2Vec2 anchorB = parseVec2(parseLine(reader, "anchorB"));

	bool collideConnected = std::stoi(parseLine(reader, "collideConnected"));

	bool enabledMotor = std::stoi(parseLine(reader, "useMotor"));
	float motorSpeed = std::stof(parseLine(reader, "motorSpeed"));
	float maxTorque = std::stof(parseLine(reader, "maxTorque"));

	bool enableLimit = std::stoi(parseLine(reader, "enableLimit"));
	float lowerAngle = std::stof(parseLine(reader, "lowerAngle"));
	float upperAngle = std::stof(parseLine(reader, "upperAngle"));

	HingeJoint2DComponent hingeComponent{entt::null, anchorA, anchorB, collideConnected, enabledMotor, motorSpeed,
										 maxTorque, enableLimit, lowerAngle, upperAngle};
	hingeComponent.connectedBodyName = connectedBodyName;

	registry.emplace<HingeJoint2DComponent>(entity, hingeComponent);
}

void Survive::ComponentLoader::loadDistanceJoint2DComponent(entt::registry &registry, entt::entity entity,
															std::ifstream &reader)
{
	std::string connectedBodyName = parseLine(reader, "connectedBody");

	b2Vec2 anchorA = parseVec2(parseLine(reader, "anchorA"));
	b2Vec2 anchorB = parseVec2(parseLine(reader, "anchorB"));

	bool collideConnected = std::stoi(parseLine(reader, "collideConnected"));

	float minLength = std::stof(parseLine(reader, "minLength"));
	float maxLength = std::stof(parseLine(reader, "maxLength"));

	if (minLength < 0 || maxLength < 0)
	{
		return;
	}

	DistanceJoint2DComponent distanceComponent{entt::null, anchorA, anchorB, minLength, maxLength, collideConnected};
	distanceComponent.connectedBodyName = connectedBodyName;

	registry.emplace<DistanceJoint2DComponent>(entity, distanceComponent);
}

void
Survive::ComponentLoader::loadRigidBody2DComponent(entt::registry &registry, entt::entity entity, std::ifstream &reader)
{
	int bodyType = std::stoi(parseLine(reader, "bodyType"));

	if (bodyType < 0 || bodyType > 2)
	{
		return;
	}

	float linearDrag = std::stof(parseLine(reader, "linearDrag"));
	b2Vec2 linearVelocity = parseVec2(parseLine(reader, "linearVelocity"));
	float angularDrag = std::stof(parseLine(reader, "angularDrag"));

	if (linearDrag < 0 || angularDrag < 0)
	{
		return;
	}

	float gravityScale = std::stof(parseLine(reader, "gravityScale"));
	bool fixedAngle = std::stoi(parseLine(reader, "fixedAngle"));

	registry.emplace<RigidBody2DComponent>(entity, static_cast<b2BodyType>(bodyType), linearDrag, linearVelocity,
										   angularDrag, gravityScale, fixedAngle);
}

std::optional<Survive::Font>
Survive::ComponentLoader::getFont(const std::string &fontFile, const std::string &textureAtlas, Loader &loader)
{
	Font font(textureAtlas.c_str(), loader);

	if (fontFile.ends_with(".fnt"))
	{
		font.loadFontFromFntFile(fontFile);
	} else if (fontFile.ends_with(".json"))
	{
		font.loadFontFromJsonFile(fontFile);
	}

	if (font.isFontLoaded() && font.isFontTextureValid())
	{
		return font;
	}

	return {};
}

std::tuple<float, float, float> Survive::ComponentLoader::loadCollider2DComponent(std::ifstream &reader)
{
	float mass = std::stof(parseLine(reader, "mass"));
	float friction = std::stof(parseLine(reader, "friction"));
	float elasticity = std::stof(parseLine(reader, "elasticity"));

	return {mass, friction, elasticity};
}
