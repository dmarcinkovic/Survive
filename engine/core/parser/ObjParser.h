//
// Created by david on 16. 05. 2020..
//

#ifndef SURVIVE_OBJPARSER_H
#define SURVIVE_OBJPARSER_H

#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "Loader.h"

namespace Survive
{
	class ObjParser
	{
	private:
		static void processVertex(const std::vector<glm::vec3> &points, const std::vector<glm::vec3> &normals,
								  const std::vector<glm::vec2> &textureCoordinates, std::vector<float> &resultPoints,
								  std::vector<float> &resultNormals, std::vector<float> &resultTextures,
								  const std::string &line);

		static void processIndices(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &normals,
								   const std::vector<glm::vec2> &textures, std::vector<float> &resultPoints,
								   std::vector<float> &resultNormals, std::vector<float> &resultTextures,
								   std::vector<float> &resultTangents, const std::string &line);

		static void calculateTangents(const std::vector<float> &points, const std::vector<float> &textures,
									  std::vector<float> &resultTangents);

		static std::pair<glm::vec3, glm::vec3> getDeltaPosition(const std::vector<float> &points);

		static std::pair<glm::vec2, glm::vec2> getDeltaUV(const std::vector<float> &textures);

	public:
		static Model loadObj(const std::string &objFile, Loader &loader);
	};
}

#endif //SURVIVE_OBJPARSER_H
