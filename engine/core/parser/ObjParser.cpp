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
			processIndices(vertices, normals, textures, resultPoints, resultNormals, resultTextures, line);
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
										const std::string &line)
{
	auto numbers = Util::split(line, ' ');
	processVertex(vertices, normals, textures, resultPoints, resultNormals, resultTextures, numbers[1]);
	processVertex(vertices, normals, textures, resultPoints, resultNormals, resultTextures, numbers[2]);
	processVertex(vertices, normals, textures, resultPoints, resultNormals, resultTextures, numbers[3]);

	if (numbers.size() == 5)
	{
		processVertex(vertices, normals, textures, resultPoints, resultNormals, resultTextures, numbers[1]);
		processVertex(vertices, normals, textures, resultPoints, resultNormals, resultTextures, numbers[3]);
		processVertex(vertices, normals, textures, resultPoints, resultNormals, resultTextures, numbers[4]);
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
