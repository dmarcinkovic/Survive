//
// Created by david on 09.06.22..
//

#ifndef SURVIVE_TERRAINCOMPONENT_H
#define SURVIVE_TERRAINCOMPONENT_H

#include <vector>
#include <string>

#include "TexturedModel.h"

namespace Survive
{
	struct TerrainComponent
	{
		TexturedModel terrainModel;
		std::string heightMapPath;
		std::string blendMapPath;

		std::vector<std::string> texturePaths;
		std::vector<Texture> textures;

		TerrainComponent()
				: texturePaths(4), textures(4)
		{}

		TerrainComponent(const TexturedModel &model, std::vector<Texture> textures)
				: terrainModel(model), textures(std::move(textures)), texturePaths(4)
		{}
	};
}

#endif //SURVIVE_TERRAINCOMPONENT_H
