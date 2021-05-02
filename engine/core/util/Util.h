//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_UTIL_H
#define SURVIVE_UTIL_H

#include <vector>
#include <string>
#include <regex>
#include <optional>
#include <glm/glm.hpp>

#include "../../text/Character.h"

namespace Survive
{
	class Util
	{
	private:
		static Character getCharacterFromJsonFile(const std::smatch &result, float scaleW, float scaleH);

		static void removeTrailingSpaces(std::string &string);

	public:
		static float getNumber(const std::string &string, char delimiter = '=');

		static std::vector<std::string> splitByRegex(const std::string &string);

		static Character getCharacterFromFntFile(const std::vector<std::string> &line, float w, float h);

		static std::optional<Character> getCharacterFromJsonFile(const std::string &line, float scaleW, float scaleH);

		static std::vector<std::string> split(std::string string, char delimiter);

		static void processVertex(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &normals,
								  const std::vector<glm::vec2> &textures, std::vector<float> &resultPoints,
								  std::vector<float> &resultNormals, std::vector<float> &resultTextures,
								  unsigned vertexIndex, unsigned textureIndex, unsigned normalIndex);
	};
}

#endif //SURVIVE_UTIL_H
