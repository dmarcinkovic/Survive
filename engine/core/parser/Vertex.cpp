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

void Survive::Vertex::calculateTangents(const std::vector<float> &points, const std::vector<float> &textures,
										std::vector<float> &resultTangents)
{
	auto[deltaPos1, deltaPos2] = getDeltaPosition(points);
	auto[deltaUv1, deltaUv2] = getDeltaUV(textures);

	float r = 1.0f / (deltaUv1.x * deltaUv2.y - deltaUv1.y * deltaUv2.x);

	deltaPos1 *= deltaUv2.y;
	deltaPos2 *= deltaUv1.y;
	glm::vec3 tangent = r * (deltaPos1 - deltaPos2);

	resultTangents.emplace_back(tangent.x);
	resultTangents.emplace_back(tangent.y);
	resultTangents.emplace_back(tangent.z);

	resultTangents.emplace_back(tangent.x);
	resultTangents.emplace_back(tangent.y);
	resultTangents.emplace_back(tangent.z);

	resultTangents.emplace_back(tangent.x);
	resultTangents.emplace_back(tangent.y);
	resultTangents.emplace_back(tangent.z);
}

std::pair<glm::vec3, glm::vec3> Survive::Vertex::getDeltaPosition(const std::vector<float> &points)
{
	size_t pointsSize = points.size();

	glm::vec3 v0{points[pointsSize - 9], points[pointsSize - 8], points[pointsSize - 7]};
	glm::vec3 v1{points[pointsSize - 6], points[pointsSize - 5], points[pointsSize - 4]};
	glm::vec3 v2{points[pointsSize - 3], points[pointsSize - 2], points[pointsSize - 1]};

	glm::vec3 deltaPos1 = v1 - v0;
	glm::vec3 deltaPos2 = v2 - v0;

	return {deltaPos1, deltaPos2};
}

std::pair<glm::vec2, glm::vec2> Survive::Vertex::getDeltaUV(const std::vector<float> &textures)
{
	size_t texturesSize = textures.size();

	glm::vec2 uv0{textures[texturesSize - 6], textures[texturesSize - 5]};
	glm::vec2 uv1{textures[texturesSize - 4], textures[texturesSize - 3]};
	glm::vec2 uv2{textures[texturesSize - 2], textures[texturesSize - 1]};

	glm::vec2 deltaUv1 = uv1 - uv0;
	glm::vec2 deltaUv2 = uv2 - uv0;

	return {deltaUv1, deltaUv2};
}
