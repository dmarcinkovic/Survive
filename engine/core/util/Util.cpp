//
// Created by david on 29. 03. 2020..
//

#include <cmath>
#include <random>
#include <glm/glm.hpp>

#include "Util.h"
#include "Constants.h"

std::vector<std::string> Survive::Util::splitByRegex(const std::string &string)
{
	static std::regex pattern(R"([^\s+]+)");
	std::sregex_token_iterator begin(string.begin(), string.end(), pattern);
	std::sregex_token_iterator end;

	std::vector<std::string> result;
	std::copy(std::make_move_iterator(begin), std::make_move_iterator(end), std::back_inserter(result));

	return result;
}

std::vector<std::string> Survive::Util::split(std::string string, char delimiter)
{
	std::vector<std::string> result;
	removeTrailingSpaces(string);

	unsigned int index;
	while ((index = string.find(delimiter)) != -1)
	{
		result.emplace_back(string.substr(0, index));
		string = string.substr(index + 1);
	}

	if (!string.empty())
	{
		result.emplace_back(string);
	}

	return result;
}

void Survive::Util::removeTrailingSpaces(std::string &string)
{
	while (isspace(string.back()))
	{
		string.pop_back();
	}
}

void Survive::Util::processVertex(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &normals,
								  const std::vector<glm::vec2> &textures, std::vector<float> &resultPoints,
								  std::vector<float> &resultNormals, std::vector<float> &resultTextures,
								  unsigned vertexIndex, unsigned textureIndex, unsigned normalIndex)
{
	const auto &point = vertices[vertexIndex];
	resultPoints.emplace_back(point.x);
	resultPoints.emplace_back(point.y);
	resultPoints.emplace_back(point.z);

	const auto &texture = textures[textureIndex];
	resultTextures.emplace_back(texture.x);
	resultTextures.emplace_back(texture.y);

	const auto &normal = normals[normalIndex];
	resultNormals.emplace_back(normal.x);
	resultNormals.emplace_back(normal.y);
	resultNormals.emplace_back(normal.z);
}

float Survive::Util::getRandom(float first, float second)
{
	static std::random_device device;
	static std::mt19937_64 mt(device());
	std::uniform_real_distribution<float> distribution(first, second);

	return distribution(mt);
}

ImVec2 Survive::Util::getScreenPos(const Camera &camera, const glm::mat4 &transformationMatrix,
								   const glm::vec3 &point, float x, float y, float width, float height)
{
	glm::mat4 projectionMatrix = camera.getOrthographicProjectionMatrix();
	glm::vec4 clipSpace = glm::vec4(point, 1) * transformationMatrix * projectionMatrix;

	glm::vec3 normalizedDeviceSpace{clipSpace};
	glm::vec3 viewportSpace = normalizedDeviceSpace * 0.5f + 0.5f;

	return {x + viewportSpace.x * width, y + height - viewportSpace.y * height};
}

ImVec2 Survive::Util::getScreenPos(const Camera &camera, const glm::mat4 &transformationMatrix,
								   const glm::vec2 &point, float x, float y, float width, float height)
{
	return getScreenPos(camera, transformationMatrix, glm::vec3{point, 0.0f}, x, y, width, height);
}

glm::vec3
Survive::Util::getLocalSpace(const Survive::Camera &camera, const glm::mat4 &transformationMatrix, const ImVec2 &point,
							 float x, float y, float width, float height)
{
	glm::mat4 projectionMatrix = camera.getOrthographicProjectionMatrix();

	ImVec2 screenPos(point.x - x, point.y - y);
	glm::vec2 viewport{screenPos.x / width, 1.0f - screenPos.y / height};

	glm::vec4 clipSpace{viewport * 2.0f - 1.0f, 0.0f, 1.0f};
	glm::vec4 localSpace = clipSpace * glm::inverse(projectionMatrix) * glm::inverse(transformationMatrix);

	return glm::vec3{localSpace};
}

bool Survive::Util::mouseHoversPoint(const ImVec2 &point, float radius)
{
	static constexpr float THRESHOLD = 3.0f;
	ImVec2 mousePos = ImGui::GetMousePos();

	return std::abs(mousePos.x - point.x) < radius + THRESHOLD &&
		   std::abs(mousePos.y - point.y) < radius + THRESHOLD;
}

bool Survive::Util::mouseHoversLine(const ImVec2 &p1, const ImVec2 &p2)
{
	static constexpr float THRESHOLD = 3.0f;
	ImVec2 mousePosition = ImGui::GetMousePos();

	float lineLen = lineDistance(p1, p2);

	float segmentLen1 = lineDistance(p1, mousePosition);
	float segmentLen2 = lineDistance(p2, mousePosition);

	return segmentLen1 + segmentLen2 - lineLen < THRESHOLD;
}

float Survive::Util::lineDistance(const ImVec2 &p1, const ImVec2 &p2)
{
	float dx = p1.x - p2.x;
	float dy = p1.y - p2.y;

	return std::sqrt(dx * dx + dy * dy);
}

ImVec2 Survive::Util::getCenter(const b2Vec2 &localCenter, const Camera &camera,
								const Transform3DComponent &transform, const glm::mat4 &modelMatrix,
								float x, float y, float width, float height)
{
	float scale = Constants::BOX2D_SCALE;
	glm::vec2 center{localCenter.x / scale, localCenter.y / scale};

	glm::vec2 point{center.x + transform.position.x, center.y + transform.position.y};

	return Util::getScreenPos(camera, modelMatrix, point, x, y, width, height);
}

glm::vec3 Survive::Util::getMouseRay(const Camera &camera, float x, float y, float width, float height)
{
	const glm::mat4 &projectionMatrix = camera.getProjectionMatrix();
	const glm::mat4 &viewMatrix = camera.getViewMatrix();

	ImVec2 mousePos = ImGui::GetMousePos();
	ImVec2 screenPos(mousePos.x - x, mousePos.y - y);
	glm::vec2 viewport{screenPos.x / width, 1.0f - screenPos.y / height};

	glm::vec4 clipSpace{viewport * 2.0f - 1.0f, -1.0f, 1.0f};

	glm::vec4 eyeSpace = glm::inverse(projectionMatrix) * clipSpace;
	eyeSpace = glm::vec4{eyeSpace.x, eyeSpace.y, -1.0, 0.0f};

	glm::vec3 worldSpace = glm::vec3{glm::inverse(viewMatrix) * eyeSpace};
	return worldSpace;
}

