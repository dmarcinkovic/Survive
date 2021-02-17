//
// Created by david on 17. 02. 2021..
//

#include "TerrainGenerator.h"

Model TerrainGenerator::generateTerrain(Loader &loader)
{
	int numberOfVertices = VERTEX_COUNT * VERTEX_COUNT;

	std::vector<float> vertices(numberOfVertices * 3);
	std::vector<float> normals(numberOfVertices * 3);
	std::vector<float> textureCoordinates(numberOfVertices * 2);

	calculateVertexInfo(vertices, normals, textureCoordinates);
	std::vector<unsigned> indices = generateIndices();

	return loader.loadToVao(vertices, textureCoordinates, normals, indices);
}

void TerrainGenerator::calculateVertexInfo(std::vector<float> &vertices, std::vector<float> &normals,
										   std::vector<float> &textureCoordinates)
{
	int vertexIndex = 0;
	for (int i = 0; i < VERTEX_COUNT; ++i)
	{
		for (int j = 0; j < VERTEX_COUNT; ++j)
		{
			setVertices(vertexIndex, vertices, i, j);
			setNormals(vertexIndex, normals);
			setTextureCoordinates(vertexIndex, textureCoordinates, i, j);

			++vertexIndex;
		}
	}
}

std::vector<unsigned> TerrainGenerator::generateIndices()
{
	std::vector<unsigned> indices;
	for (int i = 0; i < VERTEX_COUNT - 1; ++i)
	{
		for (int j = 0; j < VERTEX_COUNT - 1; ++j)
		{
			int topLeft = i * VERTEX_COUNT + j;
			int topRight = topLeft + 1;
			int bottomLeft = (i + 1) * VERTEX_COUNT + j;
			int bottomRight = bottomLeft + 1;

			indices.emplace_back(topLeft);
			indices.emplace_back(bottomLeft);
			indices.emplace_back(topRight);
			indices.emplace_back(topRight);
			indices.emplace_back(bottomLeft);
			indices.emplace_back(bottomRight);
		}
	}

	return indices;
}

void TerrainGenerator::setVertices(int index, std::vector<float> &vertices, int x, int y)
{
	vertices[index * 3] = static_cast<float>(y) / (VERTEX_COUNT - 1);
	vertices[index * 3 + 1] = 0;
	vertices[index * 3 + 2] = static_cast<float>(x) / (VERTEX_COUNT - 1);
}

void TerrainGenerator::setNormals(int index, std::vector<float> &normals)
{
	normals[index * 3] = 0;
	normals[index * 3 + 1] = 1;
	normals[index * 3 + 2] = 0;
}

void TerrainGenerator::setTextureCoordinates(int index, std::vector<float> &textureCoordinates, int x, int y)
{
	textureCoordinates[index * 2] = static_cast<float>(y) / (VERTEX_COUNT - 1);
	textureCoordinates[index * 2 + 1] = static_cast<float>(x) / (VERTEX_COUNT - 1);
}
