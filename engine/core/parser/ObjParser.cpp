//
// Created by david on 16. 05. 2020..
//

#include <fstream>
#include <numeric>

#include "ObjParser.h"
#include "Vertex.h"
#include "Util.h"

Survive::Model Survive::ObjParser::loadObj(const std::string &objFile, Loader &loader)
{
	std::ifstream reader(objFile);

	if (!reader || !objFile.ends_with("obj"))
	{
		std::string message = "Could not load " + objFile;
		throw std::runtime_error(message);
	}

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec3> normals;

	std::vector<float> resultPoints;
	std::vector<float> resultNormals;
	std::vector<float> resultTextures;
	std::vector<float> tangents;

	std::string line;
	while (std::getline(reader, line))
	{
		auto numbers = Util::split(line, ' ');

		if (line.starts_with("vn"))
		{
			float x = std::stof(numbers[1]);
			float y = std::stof(numbers[2]);
			float z = std::stof(numbers[3]);
			normals.emplace_back(x, y, z);
		} else if (line.starts_with("vt"))
		{
			float x = std::stof(numbers[1]);
			float y = std::stof(numbers[2]);
			textures.emplace_back(x, y);
		} else if (line.starts_with('v'))
		{
			float x = std::stof(numbers[1]);
			float y = std::stof(numbers[2]);
			float z = std::stof(numbers[3]);
			vertices.emplace_back(x, y, z);
		} else if (line.starts_with('f'))
		{
			processIndices(vertices, normals, textures, resultPoints, resultNormals, resultTextures, tangents, line);
		}
	}

	std::vector<unsigned> indices(resultPoints.size() / 3);
	std::iota(indices.begin(), indices.end(), 0);

	reader.close();
	return loader.loadToVao(resultPoints, resultTextures, resultNormals, indices);
}

void Survive::ObjParser::processIndices(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &normals,
										const std::vector<glm::vec2> &textures, std::vector<float> &resultPoints,
										std::vector<float> &resultNormals, std::vector<float> &resultTextures,
										std::vector<float> &resultTangents, const std::string &line)
{
	auto numbers = Util::split(line, ' ');
	processVertex(vertices, normals, textures, resultPoints, resultNormals, resultTextures, numbers[1]);
	processVertex(vertices, normals, textures, resultPoints, resultNormals, resultTextures, numbers[2]);
	processVertex(vertices, normals, textures, resultPoints, resultNormals, resultTextures, numbers[3]);
	calculateTangents(resultPoints, resultTextures, resultTangents);

	if (numbers.size() == 5)
	{
		processVertex(vertices, normals, textures, resultPoints, resultNormals, resultTextures, numbers[1]);
		processVertex(vertices, normals, textures, resultPoints, resultNormals, resultTextures, numbers[3]);
		processVertex(vertices, normals, textures, resultPoints, resultNormals, resultTextures, numbers[4]);
		calculateTangents(resultPoints, resultTextures, resultTangents);
	}
}

void Survive::ObjParser::processVertex(const std::vector<glm::vec3> &points, const std::vector<glm::vec3> &normals,
									   const std::vector<glm::vec2> &textureCoordinates,
									   std::vector<float> &resultPoints,
									   std::vector<float> &resultNormals, std::vector<float> &resultTextures,
									   const std::string &line)
{
	auto index = Util::split(line, '/');

	unsigned vertexIndex = std::stoi(index[0]) - 1;
	unsigned textureIndex = std::stoi(index[1]) - 1;
	unsigned normalIndex = std::stoi(index[2]) - 1;

	Vertex::processVertex(points, normals, textureCoordinates,
						resultPoints, resultNormals, resultTextures,
						vertexIndex, textureIndex, normalIndex);
}

void Survive::ObjParser::calculateTangents(const std::vector<float> &points, const std::vector<float> &textures,
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

std::pair<glm::vec3, glm::vec3> Survive::ObjParser::getDeltaPosition(const std::vector<float> &points)
{
	size_t pointsSize = points.size();

	glm::vec3 v0{points[pointsSize - 9], points[pointsSize - 8], points[pointsSize - 7]};
	glm::vec3 v1{points[pointsSize - 6], points[pointsSize - 5], points[pointsSize - 4]};
	glm::vec3 v2{points[pointsSize - 3], points[pointsSize - 2], points[pointsSize - 1]};

	glm::vec3 deltaPos1 = v1 - v0;
	glm::vec3 deltaPos2 = v2 - v0;

	return {deltaPos1, deltaPos2};
}

std::pair<glm::vec2, glm::vec2> Survive::ObjParser::getDeltaUV(const std::vector<float> &textures)
{
	size_t texturesSize = textures.size();

	glm::vec2 uv0{textures[texturesSize - 6], textures[texturesSize - 5]};
	glm::vec2 uv1{textures[texturesSize - 4], textures[texturesSize - 3]};
	glm::vec2 uv2{textures[texturesSize - 2], textures[texturesSize - 1]};

	glm::vec2 deltaUv1 = uv1 - uv0;
	glm::vec2 deltaUv2 = uv2 - uv0;

	return {deltaUv1, deltaUv2};
}
