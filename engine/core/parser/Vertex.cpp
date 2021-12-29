//
// Created by david on 29. 12. 2021..
//

#include "Vertex.h"

void Survive::Vertex::processVertex(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &normals,
									const std::vector<glm::vec2> &textures, std::vector<float> &resultPoints,
									std::vector<float> &resultNormals, std::vector<float> &resultTextures,
									unsigned int vertexIndex, unsigned int textureIndex, unsigned int normalIndex)
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
