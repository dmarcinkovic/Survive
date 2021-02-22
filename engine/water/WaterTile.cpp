//
// Created by david on 22. 02. 2021..
//

#include "WaterTile.h"

WaterTile::WaterTile(const Model &model, float centerX, float height, float centerZ, const Texture &duDvMap,
					 const Texture &normalMap)
		: Entity(TexturedModel(model, 0), glm::vec3{centerX, height, centerZ},
				 glm::vec3{TILE_SIZE, TILE_SIZE, TILE_SIZE}), m_DuDvMap(duDvMap), m_NormalMap(normalMap)
{

}

const Texture &WaterTile::getNormalMap() const
{
	return m_NormalMap;
}

const Texture &WaterTile::getDuDvMap() const
{
	return m_DuDvMap;
}
