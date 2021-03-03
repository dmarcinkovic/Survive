//
// Created by david on 17. 02. 2021..
//

#include <iostream>
#include "TerrainGenerator.h"
#include "../texture/stb_image.h"

Model TerrainGenerator::generateTerrain(Loader &loader, const char *heightMap)
{
	int width, height;
	std::uint8_t *image = loadHeightMap(heightMap, width, height);

	std::vector<float> vertices, normals, textureCoordinates;

	calculateVertexInfo(vertices, normals, textureCoordinates, image, width, height);
	std::vector<unsigned> indices = generateIndices(width, height);

	stbi_image_free(image);
	return loader.loadToVao(vertices, textureCoordinates, normals, indices);
}

void TerrainGenerator::calculateVertexInfo(std::vector<float> &vertices, std::vector<float> &normals,
										   std::vector<float> &textureCoordinates, const std::uint8_t *image, int width,
										   int height)
{
	int numberOfVertices = width * height;
	auto imageWidth = static_cast<float>(width);
	auto imageHeight = static_cast<float>(height);

	vertices.reserve(3 * numberOfVertices);
	normals.reserve(3 * numberOfVertices);
	textureCoordinates.reserve(2 * numberOfVertices);

	auto terrainHeight = preprocessHeight(image, width, height);

	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			auto x = static_cast<float>(i);
			auto y = static_cast<float>(j);

			setVertices(vertices, x, y, terrainHeight[j][i], imageWidth, imageHeight);
			setNormals(normals, x, y, width, height, terrainHeight);
			setTextureCoordinates(textureCoordinates, x, y, imageWidth, imageHeight);
		}
	}
}

std::vector<unsigned> TerrainGenerator::generateIndices(int width, int height)
{
	std::vector<unsigned> indices;
	for (int y = 0; y < height - 1; ++y)
	{
		for (int x = 0; x < width - 1; ++x)
		{
			int topLeft = y * width + x;
			int topRight = topLeft + 1;
			int bottomLeft = (y + 1) * width + x;
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

void TerrainGenerator::setVertices(std::vector<float> &vertices, float x, float y, float terrainHeight, float width,
								   float height)
{
	vertices.emplace_back(y / (height - 1));
	vertices.emplace_back(-terrainHeight);
	vertices.emplace_back(x / (width - 1));
}

void TerrainGenerator::setNormals(std::vector<float> &normals, int x, int y, int width, int height,
								  const std::vector<std::vector<float>> &terrainHeight)
{
	glm::vec3 normal = calculateNormal(x, y, width, height, terrainHeight);

	normals.emplace_back(normal.x);
	normals.emplace_back(normal.y);
	normals.emplace_back(normal.z);
}

void TerrainGenerator::setTextureCoordinates(std::vector<float> &textureCoordinates, float x, float y, float width,
											 float height)
{
	textureCoordinates.emplace_back(y / (height - 1));
	textureCoordinates.emplace_back(x / (width - 1));
}

std::uint8_t *TerrainGenerator::loadHeightMap(const char *heightMap, int &width, int &height)
{
	stbi_set_flip_vertically_on_load(1);

	int BPP;
	std::uint8_t *image = stbi_load(heightMap, &width, &height, &BPP, 4);

	if (!image)
	{
		std::cout << "Error while loading image " << height << '\n';
		return nullptr;
	}

	return image;
}

float TerrainGenerator::getHTerrainHeight(int x, int y, const std::uint8_t *image, int imageWidth)
{
	int index = 4 * (y * imageWidth + x);

	std::uint8_t red = image[index];
	std::uint8_t green = image[index + 1];
	std::uint8_t blue = image[index + 2];

	float greyScale = static_cast<float>(red + green + blue) / 3.0f;
	float height = greyScale / 255.0f;

	return 2 * height * MAX_HEIGHT - MAX_HEIGHT;
}

std::vector<std::vector<float>> TerrainGenerator::preprocessHeight(const std::uint8_t *image, int width, int height)
{
	std::vector<std::vector<float>> result(height, std::vector<float>(width));

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			result[y][x] = getHTerrainHeight(x, y, image, width);
		}
	}

	return result;
}

glm::vec3 TerrainGenerator::calculateNormal(int x, int y, int width, int height,
											const std::vector<std::vector<float>> &terrainHeight)
{
	float heightL = getPreprocessedValue(x - 1, y, height, width, terrainHeight);
	float heightR = getPreprocessedValue(x + 1, y, height, width, terrainHeight);
	float heightD = getPreprocessedValue(x, y - 1, height, width, terrainHeight);
	float heightU = getPreprocessedValue(x, y + 1, height, width, terrainHeight);

	glm::vec3 normal{heightL - heightR, 2.0f, heightD - heightU};

	return glm::normalize(normal);
}

float
TerrainGenerator::getPreprocessedValue(int i, int j, int rows, int cols, const std::vector<std::vector<float>> &matrix)
{
	if (i < 0 || i >= cols || j < 0 || j >= rows)
	{
		return 0;
	}

	return matrix[i][j];
}
