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
	static constexpr int VERTEX_COUNT = 128;
	static constexpr float MAX_HEIGHT = 30;

public:
	static Model generateTerrain(Loader &loader, const char *heightMap);

private:
	static void calculateVertexInfo(std::vector<float> &vertices, std::vector<float> &normals,
									std::vector<float> &textureCoordinates);

	static std::vector<unsigned> generateIndices();

	static void setVertices(int index, std::vector<float> &vertices, int x, int y);

	static void setNormals(int index, std::vector<float> &normals);

	static void setTextureCoordinates(int index, std::vector<float> &textureCoordinates, int x, int y);

	static std::uint8_t *loadHeightMap(const char *heightMap, int &width, int &height);

	static float getHeight(int x, int y, const std::uint8_t *image, int imageWidth, int imageHeight);
};


#endif //SURVIVE_TERRAINGENERATOR_H
