//
// Created by david on 29. 03. 2020..
//

#include <cmath>
#include <random>
#include <glm/glm.hpp>

#include "Util.h"

std::vector<std::string> Survive::Util::splitByRegex(const std::string &string)
{
	static std::regex pattern(R"([^\s+]+)");
	std::sregex_token_iterator begin(string.begin(), string.end(), pattern);
	std::sregex_token_iterator end;

	std::vector<std::string> result;
	std::copy(std::make_move_iterator(begin), std::make_move_iterator(end), std::back_inserter(result));

	return result;
}

float Survive::Util::getNumber(const std::string &string, char delimiter)
{
	unsigned int index = string.find(delimiter);
	return std::stof(string.substr(index + 1));
}

Survive::Character Survive::Util::getCharacterFromFntFile(const std::vector<std::string> &line, float w, float h)
{
	int id = std::floor(getNumber(line[1]));
	float x = getNumber(line[2]);
	float y = getNumber(line[3]);
	float width = getNumber(line[4]);
	float height = getNumber(line[5]);
	float xOffset = getNumber(line[6]);
	float yOffset = -getNumber(line[7]);
	float advance = getNumber(line[8]);

	return {id, x, y, width, height, xOffset, yOffset, advance, w, h};
}

std::optional<Survive::Character>
Survive::Util::getCharacterFromJsonFile(const std::string &line, float scaleW, float scaleH)
{
	static std::string pattern = R"(\s+\"(.?.?)\":\{\"x\":(\d+),\"y\":(\d+),\"width\":(\d+),\"height\")"
								 R"(:(\d+),\"originX\":(-?\d+),\"originY\":(-?\d+),\"advance\":(\d+))";
	static std::regex regex(pattern);
	std::smatch result;
	std::regex_search(line, result, regex);

	if (result.empty())
	{
		return {};
	}

	return getCharacterFromJsonFile(result, scaleW, scaleH);
}

Survive::Character Survive::Util::getCharacterFromJsonFile(const std::smatch &result, float scaleW, float scaleH)
{
	int id = result[1].str().length() == 2 ? result[1].str()[1] : result[1].str()[0];
	float x = std::stof(result[2].str());
	float y = std::stof(result[3].str());
	float width = std::stof(result[4].str());
	float height = std::stof(result[5].str());
	float xOffset = std::stof(result[6].str());
	float yOffset = std::stof(result[7].str());
	float advance = std::stof(result[8].str());

	return {id, x, y, width, height, xOffset, yOffset, advance, scaleW, scaleH};
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
	static std::uniform_real_distribution<float> distribution(first, second);

	return distribution(mt);
}


