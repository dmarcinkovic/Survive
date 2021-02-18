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

	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			auto x = static_cast<float>(i);
			auto y = static_cast<float>(j);

			float terrainHeight = getHTerrainHeight(i, j, image, width, height);

			setVertices(vertices, x, y, terrainHeight, imageWidth, imageHeight);
			setNormals(normals);
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

void TerrainGenerator::setNormals(std::vector<float> &normals)
{
	normals.emplace_back(0);
	normals.emplace_back(1);
	normals.emplace_back(0);
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

float TerrainGenerator::getHTerrainHeight(int x, int y, const std::uint8_t *image, int imageWidth, int imageHeight)
{
	if (x < 0 || x >= imageWidth || y < 0 || y >= imageHeight)
	{
		return 0;
	}

	int index = 4 * (y * imageWidth + x);

	std::uint8_t red = image[index];
	std::uint8_t green = image[index + 1];
	std::uint8_t blue = image[index + 2];

	float greyScale = static_cast<float>(red + green + blue) / 3.0f;
	float height = greyScale / 255.0f;

	return  2 * height * MAX_HEIGHT - MAX_HEIGHT;
}
