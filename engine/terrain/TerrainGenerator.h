//
// Created by david on 17. 02. 2021..
//

#ifndef SURVIVE_TERRAINGENERATOR_H
#define SURVIVE_TERRAINGENERATOR_H

#include <vector>
#include <cstdint>

#include "../renderer/Loader.h"

class TerrainGenerator
{
private:
	static constexpr float MAX_HEIGHT = 30;

public:
	static Model generateTerrain(Loader &loader, const char *heightMap);

private:
	static void calculateVertexInfo(std::vector<float> &vertices, std::vector<float> &normals,
									std::vector<float> &textureCoordinates, const std::uint8_t *image, int width,
									int height);

	static std::vector<unsigned> generateIndices(int width, int height);

	static void
	setVertices(std::vector<float> &vertices, float x, float y, float terrainHeight, float width, float height);

	static void setNormals(std::vector<float> &normals);

	static void setTextureCoordinates(std::vector<float> &textureCoordinates, float x, float y, float width, float height);

	static std::uint8_t *loadHeightMap(const char *heightMap, int &width, int &height);

	static float getHTerrainHeight(int x, int y, const std::uint8_t *image, int imageWidth, int imageHeight);
};


#endif //SURVIVE_TERRAINGENERATOR_H
