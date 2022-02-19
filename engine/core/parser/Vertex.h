//
// Created by david on 29. 12. 2021..
//

#ifndef SURVIVE_VERTEX_H
#define SURVIVE_VERTEX_H

#include <vector>
#include <glm/glm.hpp>

namespace Survive
{
	class Vertex
	{
	private:
		static std::pair<glm::vec3, glm::vec3> getDeltaPosition(const std::vector<float> &points);

		static std::pair<glm::vec2, glm::vec2> getDeltaUV(const std::vector<float> &textures);

	public:
		static void processVertex(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &normals,
								  const std::vector<glm::vec2> &textures, std::vector<float> &resultPoints,
								  std::vector<float> &resultNormals, std::vector<float> &resultTextures,
								  unsigned vertexIndex, unsigned textureIndex, unsigned normalIndex);

		static void calculateTangents(const std::vector<float> &points, const std::vector<float> &textures,
									  std::vector<float> &resultTangents);

	};
}

#endif //SURVIVE_VERTEX_H
