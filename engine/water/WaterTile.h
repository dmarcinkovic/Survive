//
// Created by david on 22. 02. 2021..
//

#ifndef SURVIVE_WATERTILE_H
#define SURVIVE_WATERTILE_H


#include "../entity/Entity.h"

class WaterTile : public Entity
{
private:
	static constexpr int TILE_SIZE = 200;

	Texture m_DuDvMap;
	Texture m_NormalMap;

public:
	WaterTile(const Model &model, float centerX, float  height, float centerZ, const Texture &duDvMap, const Texture &normalMap);

	[[nodiscard]] const Texture &getNormalMap() const;

	[[nodiscard]] const Texture &getDuDvMap() const;
};


#endif //SURVIVE_WATERTILE_H
