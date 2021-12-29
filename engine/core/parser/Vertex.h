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
	public:
		static void processVertex(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &normals,
								  const std::vector<glm::vec2> &textures, std::vector<float> &resultPoints,
								  std::vector<float> &resultNormals, std::vector<float> &resultTextures,
								  unsigned vertexIndex, unsigned textureIndex, unsigned normalIndex);
	};
}

#endif //SURVIVE_VERTEX_H
