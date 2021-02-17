//
// Created by david on 17. 02. 2021..
//

#ifndef SURVIVE_TERRAINGENERATOR_H
#define SURVIVE_TERRAINGENERATOR_H

#include <vector>

#include "../renderer/Loader.h"

class TerrainGenerator
{
private:
	static constexpr int VERTEX_COUNT = 128;

public:
	static Model generateTerrain(Loader &loader);

private:
	static void calculateVertexInfo(std::vector<float> &vertices, std::vector<float> &normals,
									std::vector<float> &textureCoordinates);

	static std::vector<unsigned> generateIndices();

	static void setVertices(int index, std::vector<float> &vertices, int x, int y);

	static void setNormals(int index, std::vector<float> &normals);

	static void setTextureCoordinates(int index, std::vector<float> &textureCoordinates, int x, int y);
};


#endif //SURVIVE_TERRAINGENERATOR_H
